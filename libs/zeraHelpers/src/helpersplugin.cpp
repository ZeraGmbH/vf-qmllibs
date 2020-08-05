#include "helpersplugin.h"
#include <QCoreApplication>
#include <QtQml/QtQml>



void HelpersPlugin::init()
{
    HelpersPlugin* obj= new HelpersPlugin();
    obj->registerTypes("QmlHelpers");
}



void HelpersPlugin::registerTypes(const char* uri) {
    // Register config interface
    qmlRegisterSingletonType(QUrl("qrc:/src/qml/ZeraLocale.qml"), "ZeraLocale", 1, 0, "ZLocale");
    // Register helper functions
    qmlRegisterSingletonType(QUrl("qrc:/src/qml/TextHelper.qml"), uri, 1, 0, "TextHelper");
}


static void init(){
    HelpersPlugin::init();
}
Q_COREAPP_STARTUP_FUNCTION(init)
