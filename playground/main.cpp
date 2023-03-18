#include "advancednetworkmanager.h"
#include "globalusernotificationsingleton.h"
#include "QQmlApplicationEngine"
#include <QGuiApplication>
#include <QQmlEngine>

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/Main.qml")));

    AdvancedNetworkmanager::registerQml();
    GlobalUserNotificationSingleton::registerQml();

    return app.exec();
}
