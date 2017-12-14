#include "clientgame.h"

#include <QTextStream>
#include <QDataStream>

ClientGame::ClientGame(QObject* parent) : Game(parent)
{
    m_pSession = createNetworkSession(this);

    if (m_pSession) {
        connect(
            m_pSession, &QNetworkSession::opened,
            this, &ClientGame::on_sessionOpened);
        m_pSession->open();
    } else {
        on_sessionOpened();
    }

    new_connect();
}


void ClientGame::new_connect()
{
    m_Socket->connectToHost(
        "127.0.0.1",
        33333);
}

void ClientGame::on_sessionOpened()
{
    m_Socket = new QTcpSocket(this);
    connect(
        m_Socket, &QAbstractSocket::connected,
        this, &ClientGame::on_connected);
    connect(
        m_Socket, &QIODevice::readyRead,
        this, &ClientGame::on_readyRead);
}

void ClientGame::on_connected()
{
    QDataStream inout(m_Socket);
    QString initStr;
    inout << QString("NEWCLIENT");
}
