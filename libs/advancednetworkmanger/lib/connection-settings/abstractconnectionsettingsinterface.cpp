#include "abstractconnectionsettingsinterface.h"
#include "netmansubsettings.h"
#include <NetworkManagerQt/WirelessDevice>

void AbstractConnectionSettingsInterface::load(QString p_path)
{
    m_connection = NetworkManager::findConnection(p_path);
    if(m_connection != NULL) {
        m_settings = m_connection->settings();
        m_connectionMap = m_connection->settings()->toMap();
        emit loadComplete();
    }
    else
        create();
}

void AbstractConnectionSettingsInterface::save()
{
    NMVariantMapMap map = m_settings->toMap();
    if(map.contains("connection")) {
        if(map["connection"].contains("interface-name"))
            map["connection"].remove("interface-name");

        if(map.contains("802-11-wireless")) {
            if(map["802-11-wireless"].contains("mac-address"))
                map["802-11-wireless"].remove("mac-address");
        }
    }

    NetworkManager::Ipv4Setting::Ptr ipv4Settings = NetManSubSettings::getIpv4Settings(m_settings);
    if (ipv4Settings) {
        if (ipv4Settings->method() == NetworkManager::Ipv4Setting::ConfigMethod::Automatic) {
            if(map.contains("ipv4")) {
                if(map["ipv4"].contains("addresses"))
                    map["ipv4"].remove("addresses");
                if(map["ipv4"].contains("address-data"))
                    map["ipv4"].remove("address-data");
            }
        }
    }

    NetworkManager::Ipv6Setting::Ptr ipv6Settings = NetManSubSettings::getIpv6Settings(m_settings);
    if(ipv6Settings) {
        if(map.contains("ipv6")) {
            if(map["ipv6"].contains("addresses"))
                map["ipv6"].remove("addresses");
            if(map["ipv6"].contains("address-data"))
                map["ipv6"].remove("address-data");
        }
    }

    if(m_connection != NULL)
        m_connection->update(map);
    else {
        NetworkManager::addConnection(map);
        m_settings.clear();
    }
}

void AbstractConnectionSettingsInterface::saveAndActivate(const QString &p_devUni,const QString &p_apPath)
{
    if(m_connection == NULL){
        NMVariantMapMap map = m_settings->toMap();
        NetworkManager::addAndActivateConnection(map,p_devUni,"");
        m_settings.clear();
    }
}

void AbstractConnectionSettingsInterface::discard()
{
    if(m_connection != NULL)
        m_connection->updateUnsaved(m_connectionMap);
    else
        m_settings.clear();
}

QString AbstractConnectionSettingsInterface::getDevicePath(const QString &p_interfaceName)
{
    return QString();
}

QString AbstractConnectionSettingsInterface::getHostName()
{
    QString retVal;
    retVal = NetworkManager::hostname();
    if(!retVal.contains("zera-")){
        retVal="";
    }
    return retVal;
}

QString AbstractConnectionSettingsInterface::getDevice()
{
    if(m_connection != NULL){
        return m_settings->interfaceName();
    }else{
        return "";
    }
}

void AbstractConnectionSettingsInterface::setDevice(QString &device)
{
    if(m_settings != nullptr){
        m_settings->setInterfaceName(device);
        emit deviceChanged();
    }
}

QString AbstractConnectionSettingsInterface::getConName()
{

    QString ret = "";

    if(m_connection !=  NULL){
        ret = m_settings->id();
    }
    return ret;
}

void AbstractConnectionSettingsInterface::setConName(QString p_conName)
{
    if(m_settings != nullptr){
        m_settings->setId(p_conName);
        emit conNameChanged();
    }
}
