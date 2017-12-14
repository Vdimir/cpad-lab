#ifndef CLIENTGAME_H
#define CLIENTGAME_H

#include "game.h"
#include "netsession.h"

#include <QTcpSocket>

class ClientGame: public Game {
    Q_OBJECT
  public:
    explicit ClientGame(QObject* parent = 0);

    QTcpSocket* m_pSocket;

    QNetworkSession* m_pSession;

    void new_connect();

  public slots:
    void ping();
    void on_readyRead();
    void on_connected();
    void on_sessionOpened();
};

#endif // CLIENTGAME_H
