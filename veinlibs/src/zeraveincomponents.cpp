#include "zeraveincomponents.h"
#include <QCoreApplication>
#include <QtQml/QtQml>
#include <zeratranslationplugin.h>

void ZeraVeinComponents::init()
{
    ZeraVeinComponents* obj= new ZeraVeinComponents();
    obj->registerTypes("ZeraVeinComponents");
}

void ZeraVeinComponents::registerTypes(const char* uri)
{
    // Dependencies
    ZeraTranslationPlugin::registerQml();
    // Own
    qmlRegisterType(QUrl("qrc:/src/qml/VFComboBox.qml"),uri,1,0,"VFComboBox");
    qmlRegisterType(QUrl("qrc:/src/qml/VFLineEdit.qml"),uri,1,0,"VFLineEdit");
    qmlRegisterType(QUrl("qrc:/src/qml/VFSpinBox.qml"),uri,1,0,"VFSpinBox");
    qmlRegisterType(QUrl("qrc:/src/qml/VFSwitch.qml"),uri,1,0,"VFSwitch");
}

static void init(){
    ZeraVeinComponents::init();
}
Q_COREAPP_STARTUP_FUNCTION(init)
