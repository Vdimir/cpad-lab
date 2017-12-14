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
  signals:

  public slots:
    virtual void ping() = 0;
};


#endif // GAME_H
