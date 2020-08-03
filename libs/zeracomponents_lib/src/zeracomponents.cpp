#include "zeracomponents.h"
#include <QCoreApplication>
#include <QtQml/QtQml>

void ZeraComponents::init()
{
    ZeraComponents* obj= new ZeraComponents();
    obj->registerTypes("ZeraComponents");
}



void ZeraComponents::registerTypes(const char* uri) {
    // Register config interface
    qmlRegisterSingletonType(QUrl("qrc:/src/qml/ZeraComponentsConfig.qml"), "ZeraComponentsConfig", 1, 0, "ZCC");
    // Register controls
    qmlRegisterType(QUrl("qrc:/src/qml/ZButton.qml"),uri,1,0,"ZButton");
    qmlRegisterType(QUrl("qrc:/src/qml/ZComboBox.qml"),uri,1,0,"ZComboBox");
    qmlRegisterType(QUrl("qrc:/src/qml/ZDoubleValidator.qml"),uri,1,0,"ZDoubleValidator");
    qmlRegisterType(QUrl("qrc:/src/qml/ZLineEdit.qml"),uri,1,0,"ZLineEdit");
    qmlRegisterType(QUrl("qrc:/src/qml/ZSpinBox.qml"),uri,1,0,"ZSpinBox");
    qmlRegisterType(QUrl("qrc:/src/qml/ZUnitComboBox.qml"),uri,1,0,"ZUnitComboBox");
    qmlRegisterType(QUrl("qrc:/src/qml/ZVisualComboBox.qml"),uri,1,0,"ZVisualComboBox");
}


static void init(){
    ZeraComponents::init();
}
Q_COREAPP_STARTUP_FUNCTION(init)
