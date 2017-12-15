#include "netsession.h"


#include <QNetworkConfigurationManager>


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
