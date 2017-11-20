#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>

#include "table_window.h"

class MainWindow : public QMainWindow, Ui::MainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private:
  private slots:
    void on_actionOpen_triggered();
    void on_actionClose_All_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
};

#endif // MAIN_WINDOW_H
