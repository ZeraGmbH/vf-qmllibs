#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <QApplication>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickView>
#include <QDebug>
#include <QDir>
#include <QFont>


#include <QQmlDebuggingEnabler>


//#include "vfnetworkmanager.h"





int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    qDebug() << "Starting vf-qmllibs playground";

    QApplication app(argc, argv);
    QFont fon("Helvetica");

     QQmlDebuggingEnabler enabler;

     //VfNetworkManager::init();

    QQmlApplicationEngine engine;




    //This following line is not neccesary, if you run in qtCreator
    //For more information take a look into the Readmes
    //engine.addImportPath("<your path>/usr/lib64/zera-qml-modules");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }








    return app.exec();

}
