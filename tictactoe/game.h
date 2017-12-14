#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "tictactoe.h"

class Game : public QObject {
    Q_OBJECT
  public:
    explicit Game(QObject* parent = 0);
    TicTacToeGame tic;
    CellState myFigure;
    int turnNumber;

    virtual ~Game();

    QTcpSocket* m_Socket;

  signals:
    void youTurn(bool);
    void statusChanged(QString);

  public slots:
    virtual void new_turn(QString turn);
    void on_readyRead();
};


#endif // GAME_H
