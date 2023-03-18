#include "helpersplugin.h"
#include <QtQml>

bool HelpersPlugin::m_wasRegistered = false;

void HelpersPlugin::registerQml()
{
    if(!m_wasRegistered) {
        registerTypes("QmlHelpers");
        m_wasRegistered = true;
    }
}

void HelpersPlugin::registerTypes(const char* uri) {
    // Register config interface
    qmlRegisterSingletonType(QUrl("qrc:/qml/ZeraLocale.qml"), "ZeraLocale", 1, 0, "ZLocale");
    // Register helper functions
    qmlRegisterSingletonType(QUrl("qrc:/qml/TextHelper.qml"), uri, 1, 0, "TextHelper");
}
