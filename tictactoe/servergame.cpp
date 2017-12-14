#include "servergame.h"
#include <QDataStream>

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
        QString strErrors;// = m_pTextEditErrors->toPlainText();
        strErrors += QString("Error: ") + m_pServer->errorString();

        qDebug() << strErrors;
    }
}


void ServerGame::on_newConnection()
{
    qDebug() << "new connection";
    pClientSocket = m_pServer->nextPendingConnection();
    connect(
        pClientSocket, &QAbstractSocket::disconnected,
        pClientSocket, &QObject::deleteLater);

    connect(
        pClientSocket, &QIODevice::readyRead,
        this, &ServerGame::on_readyRead);
}

void ServerGame::on_readyRead()
{
    QTcpSocket* pClientSocket =
        qobject_cast <QTcpSocket*> (sender());

    if (!pClientSocket) {
        return;
    }

    QDataStream inout(pClientSocket);
    inout.startTransaction();
    QString strChatLine;
    inout >> strChatLine;
    qDebug() << strChatLine;

    if (!inout.commitTransaction()) {
        return;
    }

}


void ServerGame::ping()
{
    QDataStream inout(pClientSocket);
    inout << QString("from server");

}
