#include "advancednetworkmanager.h"
#include "notificationmanager.h"
#include "uivectorgraphics.h"
#include "zeracomponents.h"
#include "zvkeyboardlayout.h"
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

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    ZVKeyboardLayout::setKeyboardLayoutEnvironment();

    return app.exec();
}
