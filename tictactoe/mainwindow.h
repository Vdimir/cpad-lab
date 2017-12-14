#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>

#include <game.h>
#include <QList>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();


    bool setupGame(Game*);
    void connectButton();
  private:
    Ui::MainWindow* ui;
    Game* game;

    QList<QPushButton*> btns;

  private slots:
    void enableBtns(bool );
    void startGamePressed();
    void setStatus(QString str);
};

#endif // SERVERWINDOW_H
