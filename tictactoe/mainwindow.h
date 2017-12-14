#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>

#include <game.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();


    bool setupServer();
    bool setupClient();

  private:
    Ui::MainWindow* ui;
    Game* game;

  private slots:
    void startGamePressed();
};

#endif // SERVERWINDOW_H
