#include "zeracomponents.h"
#include <QCoreApplication>
#include <QtQml>

bool ZeraComponents::m_wasRegistered = false;

void ZeraComponents::registerQml()
{
    registerTypes("ZeraComponents");
}

void ZeraComponents::registerTypes(const char* uri) {
    Q_INIT_RESOURCE(zeracomponents);
    // Register config interface
    qmlRegisterSingletonType(QUrl("qrc:/src/qml/ZeraComponentsConfig/ZeraComponentsConfig.qml"), "ZeraComponentsConfig", 1, 0, "ZCC");
    // Register controls
    qmlRegisterType(QUrl("qrc:/src/qml/ZeraComponents/ZButton.qml"),uri,1,0,"ZButton");
    qmlRegisterType(QUrl("qrc:/src/qml/ZeraComponents/ZComboBox.qml"),uri,1,0,"ZComboBox");
    qmlRegisterType(QUrl("qrc:/src/qml/ZeraComponents/ZDoubleValidator.qml"),uri,1,0,"ZDoubleValidator");
    qmlRegisterType(QUrl("qrc:/src/qml/ZeraComponents/ZLineEdit.qml"),uri,1,0,"ZLineEdit");
    qmlRegisterType(QUrl("qrc:/src/qml/ZeraComponents/ZSpinBox.qml"),uri,1,0,"ZSpinBox");
    qmlRegisterType(QUrl("qrc:/src/qml/ZeraComponents/ZUnitComboBox.qml"),uri,1,0,"ZUnitComboBox");
    qmlRegisterType(QUrl("qrc:/src/qml/ZeraComponents/ZVisualComboBox.qml"),uri,1,0,"ZVisualComboBox");
}
