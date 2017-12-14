#ifndef SERVERGAME_H
#define SERVERGAME_H

#include "game.h"

#include "netsession.h"

class ServerGame: public Game {
    Q_OBJECT
  public:
    explicit ServerGame(QObject* parent = 0);

    //    QTcpServer* tcpServer;
    //    int server_status;

    QNetworkSession* m_pSession;
    QTcpServer* m_pServer;
  public slots:

    void on_sessionOpened();
    void on_newConnection();
};

#endif // SERVERGAME_H
