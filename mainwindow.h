#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "requestwrapper.h"
#include "lootmodel.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  private slots:
    void on_pushButton_clicked();
    void waitLeague();
    void waitResponse();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

  private:
    void processResponse(QByteArray *response);

    Ui::MainWindow *ui;
    RequestWrapper r;
    LootModel model;
    QTimer *startTimer;
    bool isPicture, isLoot;
};

#endif // MAINWINDOW_H
