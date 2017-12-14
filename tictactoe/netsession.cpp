#include "netsession.h"


#include <QNetworkConfigurationManager>


//QSharedPointer <QNetworkSession> createNetworkSession()
//{
//    QSharedPointer <QNetworkSession> ptr_session;
//    QNetworkConfigurationManager manager;

//    if (manager.capabilities() &
//            QNetworkConfigurationManager::NetworkSessionRequired) {
//        QNetworkConfiguration config = manager.defaultConfiguration();
//        ptr_session.reset(new QNetworkSession(config));
//        ptr_session->open();
//        ptr_session->waitForOpened(-1);
//    }

//    return ptr_session;
//} // createNetworkSession()

QNetworkSession* createNetworkSession(QObject* pParent)
{
    QNetworkSession* pSession = Q_NULLPTR;
    QNetworkConfigurationManager manager;

    if (manager.capabilities() &
            QNetworkConfigurationManager::NetworkSessionRequired) {
        QNetworkConfiguration config = manager.defaultConfiguration();
        pSession = new QNetworkSession(config, pParent);
    }

    //
    return pSession;
}
