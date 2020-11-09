#include "advancednetworkmanager.h"
#include <NetworkManagerQt/Device>
#include <QCoreApplication>
#include <QtQml/QtQml>
#include <zeratranslationplugin.h>
#include <QQmlEngine>

void AdvancedNetworkmanager::init()
{
    AdvancedNetworkmanager* obj= new AdvancedNetworkmanager();
    obj->registerTypes("anmsettings");
}

void AdvancedNetworkmanager::registerTypes(const char* uri)
{
    // Dependencies
    ZeraTranslationPlugin::registerQml();
    // Own
    qmlRegisterType<AbstractConnectionSettingsInterface>(uri, 1, 0, "AbstractConnectionSettingsInterface");
    qmlRegisterType<ConnectionModel>(uri, 1, 0, "ConnectionModel");
    qmlRegisterType<ConnectionTreeInterface>(uri, 1, 0, "ConnectionTreeInterface");
    qmlRegisterType<WiredConnectionSettingsInterface>(uri, 1, 0, "WiredConnectionSettingsInterface");
    qmlRegisterType<WirelessConnectionSettingsInterface>(uri, 1, 0, "WirelessConnectionSettingsInterface");
    qmlRegisterType<InfoInterface>(uri, 1, 0, "InfoInterface");
    qmlRegisterType<NetworkmanagerAbstraction>(uri, 1, 0, "NetworkmanagerAbstraction");
    qmlRegisterType<NmCppNotification>(uri,1, 0, "NmCppNotification");
}


static void init(){
    AdvancedNetworkmanager::init();
}
Q_COREAPP_STARTUP_FUNCTION(init)
