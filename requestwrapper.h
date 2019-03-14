#ifndef REQUESTWRAPPER_H
#define REQUESTWRAPPER_H

#include <QFile>
#include <QObject>
#include <QProcess>

#include <QNetworkAccessManager>


class RequestWrapper : public QObject {
    Q_OBJECT

  public:
    RequestWrapper();
    bool begin();
    void get(const QString &requestString);
    void post(const QString &requestString, QByteArray *data);
    QByteArray *getResponse();

  signals:
    void readyToRead();

  private slots:
    void ProcessWrote();
    void GotResponse(QNetworkReply *reply);

  private:
    QProcess *wmic;
    bool leagueRunning;
    QFile lockfile;
    QString auth;
    QNetworkAccessManager manager;
    QByteArray response;
    QUrl url;
};

#endif // REQUESTWRAPPER_H
