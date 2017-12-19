#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore>
#include <QtNetwork>
#include <QtNetworkAuth>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private:
    Ui::MainWindow* ui;

  protected:
    QOAuth1* auth;
    bool in_progress;

    void setHeader();
  public slots:

    void new_reply(QNetworkReply* data);
    void search();
    void enableBtn(QString);
};

#endif // MAINWINDOW_H
