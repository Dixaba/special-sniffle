#include "requestwrapper.h"

#include <QMessageBox>
#include <QNetworkReply>
#include <QTextStream>

RequestWrapper::RequestWrapper()
{
  leagueRunning = false;
  url.setScheme("https");
  url.setHost("127.0.0.1");
  wmic = nullptr;
}

bool RequestWrapper::begin()
{
  wmic = new QProcess(nullptr);
  connect(wmic, SIGNAL(readyRead()), this, SLOT(ProcessWrote()));
  wmic->start("WMIC PROCESS WHERE name='LeagueClientUx.exe' GET commandline");
  wmic->waitForFinished(5000);

  if (leagueRunning)
    {
      lockfile.open(QIODevice::ReadOnly | QIODevice::Text);
      QTextStream file(&lockfile);
      QString line = file.readLine();
      QRegExp data(".*:\\d+:(\\d+):(.*):https");

      if (data.indexIn(line) > -1)
        {
          url.setPort(data.cap(1).toInt());
          QString rawAuth = "riot:" + data.cap(2);
          auth = "Basic " + QString(rawAuth.toLatin1().toBase64());
          connect(&manager, SIGNAL(finished(QNetworkReply *)),
                  SLOT(GotResponse(QNetworkReply *)));
        }

      return true;
    }

  return false;
}

void RequestWrapper::get(const QString &requestString)
{
  url.setPath(requestString);
  QNetworkRequest request(url);
  request.setRawHeader("Authorization", auth.toLatin1());
  QNetworkReply *reply;
  reply = manager.get(request);
  reply->ignoreSslErrors();
}

void RequestWrapper::post(const QString &requestString, QByteArray *data)
{
  url.setPath(requestString);
  QNetworkRequest request(url);
  request.setRawHeader("Authorization", auth.toLatin1());
  QNetworkReply *reply;
  reply = manager.post(request, *data);
  reply->ignoreSslErrors();
}

QByteArray *RequestWrapper::getResponse()
{
  auto result = new QByteArray(response);
  response.clear();
  return result;
}

void RequestWrapper::ProcessWrote()
{
  QByteArray out;
  out = wmic->readAll();
  out.length();
  QString output(out);

  if (output.indexOf("--install-directory") > 0)
    {
      QRegExp pth("--install-directory=(.*)\"");
      pth.setMinimal(true);
      QString path;

      if (pth.indexIn(output) > -1)
        {
          path = pth.cap(1);
          lockfile.setFileName(path + "lockfile");
        }

      wmic->close();
      wmic->deleteLater();
      leagueRunning = true;
      return;
    }
}

void RequestWrapper::GotResponse(QNetworkReply *reply)
{
  if (reply->error() != QNetworkReply::NoError)
    {
      response.clear();
      QMessageBox::critical(nullptr, tr("Ошибка"),
                            tr("Бяка при выполнении запроса"));
    }
  else
    {
      response = reply->readAll();
      emit readyToRead();
    }
}

