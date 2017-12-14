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
    m_pSocket->connectToHost(
        "127.0.0.1",
        33333);
}

void ClientGame::on_sessionOpened()
{
    m_pSocket = new QTcpSocket(this);
    connect(
        m_pSocket, &QAbstractSocket::connected,
        this, &ClientGame::on_connected);
    connect(
        m_pSocket, &QIODevice::readyRead,
        this, &ClientGame::on_readyRead);
}

void ClientGame::on_connected()
{
    QDataStream inout(m_pSocket);
    inout << QString("oooooooook");
}

void ClientGame::on_readyRead()
{
    QDataStream inout(m_pSocket);
    inout.startTransaction();
    QString strChat;
    inout >> strChat;

    if (!inout.commitTransaction()) {
        return;
    }

    qDebug() << strChat;
}


void ClientGame::ping()
{
    QDataStream inout(m_pSocket);
    qDebug() << "Send data to server";
    inout << QString("from client");
}
