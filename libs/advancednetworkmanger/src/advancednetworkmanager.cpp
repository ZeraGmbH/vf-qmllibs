#include "advancednetworkmanager.h"
#include "connectiontreeinterface.h"
#include "wiredconnectionsettingsinterface.h"
#include "wirelessconnectionsettingsinterface.h"
#include "infointerface.h"
#include "networkmanagerabstraction.h"
#include <zeratranslationplugin.h>
#include <zeracomponents.h>
#include <zerafa.h>
#include <fontawesome-qml.h>
#include <helpersplugin.h>

bool AdvancedNetworkmanager::m_wasRegistered = false;

void AdvancedNetworkmanager::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        ZeraTranslationPlugin::registerQml();
        ZeraComponents::registerQml(engine);
        FontAwesomeQml::registerFonts(true, true, false);
        FontAwesomeQml::registerFAQml(&engine);
        ZeraFa::registerQml(engine);
        HelpersPlugin::registerQml(engine);

        registerCppTypes();

        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}

void AdvancedNetworkmanager::registerCppTypes()
{
    #define uri "anmsettings"
    qmlRegisterType<ConnectionModel>(uri, 1, 0, "ConnectionModel");
    qmlRegisterType<ConnectionTreeInterface>(uri, 1, 0, "ConnectionTreeInterface");
    qmlRegisterType<WiredConnectionSettingsInterface>(uri, 1, 0, "WiredConnectionSettingsInterface");
    qmlRegisterType<WirelessConnectionSettingsInterface>(uri, 1, 0, "WirelessConnectionSettingsInterface");
    qmlRegisterType<InfoInterface>(uri, 1, 0, "InfoInterface");
    qmlRegisterType<NetworkmanagerAbstraction>(uri, 1, 0, "NetworkmanagerAbstraction");
}
