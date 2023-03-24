#include "advancednetworkmanager.h"
#include "notificationmanager.h"
#include "uivectorgraphics.h"
#include "zeracomponents.h"
#include "QQmlApplicationEngine"
#include <QGuiApplication>
#include <QQmlEngine>

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/Main.qml")));

    AdvancedNetworkmanager::registerQml(engine);
    NotificationManager::registerQml(engine);
    UiVectorgraphics::registerQml();
    ZeraComponents::registerQml(engine);

    return app.exec();
}
