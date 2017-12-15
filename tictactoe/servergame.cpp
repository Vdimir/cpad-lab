#include "servergame.h"
#include <QDataStream>
#include <assert.h>

#include <QDateTime>
#include <QMessageBox>

ServerGame::ServerGame(QObject* parent) : Game(parent)
{
    m_pSession = createNetworkSession(this);

    if (m_pSession) {
        connect(
            m_pSession, &QNetworkSession::opened,
            this, &ServerGame::on_sessionOpened);
        m_pSession->open();
    } else {
        on_sessionOpened();
    }

    qDebug() << "server created";
}

void ServerGame::on_sessionOpened()
{
    m_pServer = new QTcpServer(this);
    connect(
        m_pServer, &QTcpServer::newConnection,
        this, &ServerGame::on_newConnection);

    if (!m_pServer->listen(QHostAddress::Any, 33333)) {
        QString strErrors;
        strErrors += QString("Error: ") + m_pServer->errorString();
        QMessageBox::critical(0, "Error", strErrors);

        qDebug() << strErrors;
    }

}


void ServerGame::on_newConnection()
{
    m_Socket = m_pServer->nextPendingConnection();
    connect(
        m_Socket, &QAbstractSocket::disconnected,
        m_Socket, &QObject::deleteLater);

    connect(
        m_Socket, &QIODevice::readyRead,
        this, &ServerGame::on_readyRead);
}
