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

bool AdvancedNetworkmanager::m_wasRegistered = false;

void AdvancedNetworkmanager::registerTypes(const char* uri)
{
    if(!m_wasRegistered) {
        // Dependencies
        ZeraTranslationPlugin::registerQml();
        ZeraComponents::registerQml();
        // Own
        qmlRegisterType<AbstractConnectionSettingsInterface>(uri, 1, 0, "AbstractConnectionSettingsInterface");
        qmlRegisterType<ConnectionModel>(uri, 1, 0, "ConnectionModel");
        qmlRegisterType<ConnectionTreeInterface>(uri, 1, 0, "ConnectionTreeInterface");
        qmlRegisterType<WiredConnectionSettingsInterface>(uri, 1, 0, "WiredConnectionSettingsInterface");
        qmlRegisterType<WirelessConnectionSettingsInterface>(uri, 1, 0, "WirelessConnectionSettingsInterface");
        qmlRegisterType<InfoInterface>(uri, 1, 0, "InfoInterface");
        qmlRegisterType<NetworkmanagerAbstraction>(uri, 1, 0, "NetworkmanagerAbstraction");
        qmlRegisterType<NmCppNotification>(uri,1, 0, "NmCppNotification");
        Q_INIT_RESOURCE(anmlib);
        qmlRegisterType(QUrl("qrc:/src/qml/NetworkManager.qml"),uri,1,0,"NetworkManager");

        m_wasRegistered = true;
    }
}

void AdvancedNetworkmanager::registerQml()
{
    registerTypes("anmsettings");
}
