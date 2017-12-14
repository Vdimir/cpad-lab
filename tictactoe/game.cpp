#include "game.h"

#include <QDataStream>
#include <QDateTime>

Game::Game(QObject* parent) :
    QObject(parent),
    m_Socket(0),
    myFigure(None),
    turnNumber(0)
{ }


Game::~Game()
{ }



void Game::new_turn(QString strturn)
{
    if (m_Socket == 0) {
        return;
    }

    int turn = strturn.toInt();
    this->tic.setCell(turn, this->myFigure);
    emit youTurn(false);

    QDataStream inout(m_Socket);
    inout << strturn;
}

void Game::on_readyRead()
{
    QDataStream inout(m_Socket);

    inout.startTransaction();
    QString strChatLine;
    inout >> strChatLine;
    qDebug() << strChatLine;

    if (!inout.commitTransaction()) {
        return;
    }

    if (strChatLine == "NEWCLIENT") {
        qsrand (QDateTime::currentMSecsSinceEpoch());
        QDataStream ds(m_Socket);
        char rnd = qrand();

        if (rnd < 0) {
            ds << QString("CROSS");
            this->myFigure = Zero;
            emit youTurn(false);
        } else {
            ds << QString("ZERO");
            this->myFigure = Cross;
            emit youTurn(true);
        }

        return;
    }

    if (strChatLine == "CROSS") {
        QDataStream ds(m_Socket);
        this->myFigure = Cross;
        emit youTurn(true);
        return;
    }

    if (strChatLine == "ZERO") {
        QDataStream ds(m_Socket);
        this->myFigure = Zero;
        emit youTurn(false);
        return;
    }

    assert (this->myFigure != None);
    int turn = strChatLine.toInt();
    this->tic.setCell(turn, tic.opposeTo(this->myFigure));

    emit youTurn(true);
}
