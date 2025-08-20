#include "advancednetworkmanager.h"
#include "notificationmanager.h"
#include "zeracomponents.h"
#include "zvkeyboardlayout.h"
#include "QQmlApplicationEngine"
#include <QGuiApplication>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    // vkeyboard environmen must be set before application object is created
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    ZVKeyboardLayout::setKeyboardLayoutEnvironment();

    QLocale locale = QLocale("C");
    locale.setNumberOptions(QLocale::OmitGroupSeparator | QLocale::RejectGroupSeparator);
    QLocale::setDefault(locale);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/Main.qml")));

    AdvancedNetworkmanager::registerQml(engine);
    NotificationManager::registerQml(engine);
    ZeraComponents::registerQml(engine);

    return app.exec();
}
