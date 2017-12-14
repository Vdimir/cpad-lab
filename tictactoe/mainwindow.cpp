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
    btns << ui->fieldBtn0
         << ui->fieldBtn1
         << ui->fieldBtn2
         << ui->fieldBtn3
         << ui->fieldBtn4
         << ui->fieldBtn5
         << ui->fieldBtn6
         << ui->fieldBtn7
         << ui->fieldBtn8;
    enableBtns(false);

}

void MainWindow::enableBtns(bool en)
{
    if (game != 0 && game->tic.checkWinner() != None) {
        en = false;

        if (game->tic.checkWinner() == game->myFigure) {
            setStatus("you WIN!");
        } else {
            setStatus("you LOSe!");
        }
    } else {
        if (en) {
            setStatus("Your turn...");
        } else {
            setStatus("Waiting...");
        }
    }

    for (int i = 0; i < btns.size(); ++i) {
        btns[i]->setEnabled(en);

        if (game != 0)
            switch (game->tic.get(i)) {
                case None:
                    btns[i]->setText("*");
                    break;

                case Cross:
                    btns[i]->setText("x");
                    btns[i]->setEnabled(false);
                    break;

                case Zero:
                    btns[i]->setText("0");
                    btns[i]->setEnabled(false);
                    break;

                default:
                    break;
            }

    }
}

void MainWindow::startGamePressed()
{
    if (game) {
        delete game;
        game = 0;
        enableBtns(false);
    }

    if (ui->serverRadio->isChecked()) {
        this->setupGame(new ServerGame());
    } else {
        this->setupGame(new ClientGame());
    }

    ui->startServerBtn->setText("Restart...");

}

MainWindow::~MainWindow()
{
    if (game != 0) {
        delete game;
        game = 0;
    }

    delete ui;
}


bool MainWindow::setupGame(Game* _g)
{

    if (game != 0) {
        return false;
    }

    game = _g;

    connect(game, SIGNAL(youTurn(bool)), this, SLOT(enableBtns(bool)));
    connect(game, SIGNAL(statusChanged(QString)), this, SLOT(setStatus(QString)));
    connectButton();
    return true;
}

void MainWindow::connectButton()
{
    for (int i = 0; i < btns.size(); ++i) {
        connect(btns[i], &QPushButton::released, this, [this, i] { game->new_turn(QString::number(i)); });
    }
}


void MainWindow::setStatus(QString str)
{
    ui->label->setText(str);
}
