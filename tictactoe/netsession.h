#ifndef NETSESSION_H
#define NETSESSION_H


#include <QNetworkConfigurationManager>
#include <QNetworkSession>

//QSharedPointer <QNetworkSession> createNetworkSession();

QNetworkSession* createNetworkSession(QObject* pParent);

#endif // NETSESSION_H
