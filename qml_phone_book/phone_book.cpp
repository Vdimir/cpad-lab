
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "phonemodel.h"
#include <QQuickView>

int main(int nArgC, char* apszArgV[])
{
    QGuiApplication app(nArgC, apszArgV);

    //    QQmlApplicationEngine engine(
    //        QUrl("qrc:/forms/resources/Main.qml"));


    qmlRegisterType <PhoneModel> ("it.mmcs.phonemodel", 1, 0, "PhoneModel");

    QUrl url(QStringLiteral("qrc:/forms/resources/Main.qml"));

    QQuickView view(url);

    view.show();


    return app.exec();
}
