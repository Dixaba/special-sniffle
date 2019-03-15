#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->tableView->setModel(&model);
  connect(&r, SIGNAL(readyToRead()), this, SLOT(waitResponse()));
  startTimer = new QTimer(this);
  connect(startTimer, SIGNAL(timeout()), this, SLOT(waitLeague()));
  startTimer->start(1000);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::waitLeague()
{
  if (r.begin())
    {
      startTimer->stop();
    }
}

void MainWindow::waitResponse()
{
  processResponse(r.getResponse());
}

void MainWindow::on_pushButton_clicked()
{
  isPicture = false;
  isLoot = false;
  r.get("/performance/v1/memory");
}

void MainWindow::on_pushButton_2_clicked()
{
  isPicture = false;
  isLoot = true;
  //  r.get("/lol-loot/v1/player-loot");
  QByteArray data;
  QFile file("loot.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  data = file.readAll();
  file.close();
  processResponse(new QByteArray(data));
}

void MainWindow::processResponse(QByteArray *response)
{
  QMessageBox::about(this, "response", QString::number(response->length()));

  if (isPicture)
    {
      QPixmap pic;
      pic.loadFromData(*response);
    }

  if (isLoot)
    {
      model.loadData(response);
    }

  //TODO
  delete response;
}

void MainWindow::on_pushButton_3_clicked()
{
  isPicture = true;
  isLoot = false;
  r.get("/lol-game-data/assets/v1/champion-tiles/10/10000.jpg");
}

void MainWindow::on_pushButton_4_clicked()
{
  isPicture = true;
  isLoot = false;
  r.get("/lol-game-data/assets/v1/champion-tiles/141/141002.jpg");
}
