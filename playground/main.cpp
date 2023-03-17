#include "advancednetworkmanager.h"
#include "QQmlApplicationEngine"
#include <QGuiApplication>
#include <QtQml/QQmlEngine>

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);

    AdvancedNetworkmanager::registerQml();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/Main.qml")));

    return app.exec();
}
