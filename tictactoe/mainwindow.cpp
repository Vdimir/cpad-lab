#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>

#include "servergame.h"
#include "clientgame.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game(0)
{
    ui->setupUi(this);
    connect(ui->startServerBtn, SIGNAL (released()), this, SLOT (startGamePressed()));

}

void MainWindow::startGamePressed()
{
    if (ui->serverRadio->isChecked()) {
        this->setupServer();
    } else {
        this->setupClient();
    }
}

MainWindow::~MainWindow()
{
    if (game != 0) {
        delete game;
    }

    delete ui;
}

bool MainWindow::setupServer()
{
    if (game != 0) {
        return false;
    }

    game = new ServerGame();
    connect(ui->pushButton_2, SIGNAL (released()), game, SLOT (ping()));
    return true;
}


bool MainWindow::setupClient()
{
    if (game != 0) {
        return false;
    }

    game = new ClientGame();
    connect(ui->pushButton_2, SIGNAL (released()), game, SLOT (ping()));
    return true;
}
