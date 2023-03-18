#include "advancednetworkmanager.h"
#include "abstractconnectionsettingsinterface.h"
#include "connectiontreeinterface.h"
#include "wiredconnectionsettingsinterface.h"
#include "wirelessconnectionsettingsinterface.h"
#include "infointerface.h"
#include "networkmanagerabstraction.h"
#include "nmcppnotification.h"
#include <QtQml>
#include <zeratranslationplugin.h>
#include <zeracomponents.h>
#include <zerafa.h>
#include <helpersplugin.h>

bool AdvancedNetworkmanager::m_wasRegistered = false;

void AdvancedNetworkmanager::registerQml()
{
    if(!m_wasRegistered) {
        registerTypes("anmsettings");
        m_wasRegistered = true;
    }
}

void AdvancedNetworkmanager::registerTypes(const char* uri)
{
    // Dependencies
    ZeraTranslationPlugin::registerQml();
    ZeraComponents::registerQml();
    ZeraFa::registerQml();
    HelpersPlugin::registerQml();
    // Own
    Q_INIT_RESOURCE(anmlib);
    qmlRegisterType<AbstractConnectionSettingsInterface>(uri, 1, 0, "AbstractConnectionSettingsInterface");
    qmlRegisterType<ConnectionModel>(uri, 1, 0, "ConnectionModel");
    qmlRegisterType<ConnectionTreeInterface>(uri, 1, 0, "ConnectionTreeInterface");
    qmlRegisterType<WiredConnectionSettingsInterface>(uri, 1, 0, "WiredConnectionSettingsInterface");
    qmlRegisterType<WirelessConnectionSettingsInterface>(uri, 1, 0, "WirelessConnectionSettingsInterface");
    qmlRegisterType<InfoInterface>(uri, 1, 0, "InfoInterface");
    qmlRegisterType<NetworkmanagerAbstraction>(uri, 1, 0, "NetworkmanagerAbstraction");
    qmlRegisterType<NmCppNotification>(uri,1, 0, "NmCppNotification");
    qmlRegisterType(QUrl("qrc:/src/qml/NetworkManager.qml"),uri,1,0,"NetworkManager");
}
