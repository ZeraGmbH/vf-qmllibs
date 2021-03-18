#include "wirelessconnectionsettingsinterface.h"

WirelessConnectionSettingsInterface::WirelessConnectionSettingsInterface(QObject* parent) : AbstractConnectionSettingsInterface(parent)
{

}

void WirelessConnectionSettingsInterface::saveAndActivate(const QString &p_devUni,const QString &p_apPath)
{
    if(m_settings != NULL){
        NMVariantMapMap map = m_settings->toMap();
        NetworkManager::Connection::Ptr con = NetworkManager::findConnection(p_apPath);
        if(con==NULL){
            NetworkManager::addAndActivateConnection(map,p_devUni,m_smartConnectPath);
        }else{
            NetworkManager::addAndActivateConnection(map,p_devUni,"");
        }
        m_settings.clear();
        con->remove();
    }
}

void WirelessConnectionSettingsInterface::create()
{
    m_settings= NetworkManager::ConnectionSettings::Ptr(new NetworkManager::ConnectionSettings(NetworkManager::ConnectionSettings::ConnectionType::Wireless));
    m_settings->setUuid(QUuid::createUuid().toString().remove('{').remove('}'));
    m_settings->setting(NetworkManager::Setting::SettingType::WirelessSecurity).staticCast<NetworkManager::WirelessSecuritySetting>()->setKeyMgmt(NetworkManager::WirelessSecuritySetting::KeyMgmt::WpaPsk);
    for(auto ptr : m_settings->settings()){
        ptr->setInitialized(true);
    }
    m_settings->setZone("trusted");
    NMVariantMapMap map = m_settings->toMap();
    map.remove("802-1x");
    m_settings->fromMap(map);
    //m_settings->setAutoconnect(false);
    emit loadComplete();
}

QStringList WirelessConnectionSettingsInterface::getDevices()
{   
    NetworkManager::Device::List devList = NetworkManager::networkInterfaces();
    QStringList list;
    for(NetworkManager::Device::Ptr dev : devList){
        if(dev->type() == NetworkManager::Device::Type::Wifi){
            if(NULL != dev.staticCast<NetworkManager::WirelessDevice>()->findNetwork(getSsid())){
                list.append(dev->interfaceName());
            }
        }
    }
    return list;
}

QString WirelessConnectionSettingsInterface::getDevicePath(const QString &p_interfaceName)
{
    QString path="";
    NetworkManager::Device::List devList = NetworkManager::networkInterfaces();
    for(NetworkManager::Device::Ptr dev : devList){
        if(dev->interfaceName() == p_interfaceName){
            path=dev->uni();
            m_smartConnectPath=dev.staticCast<NetworkManager::WirelessDevice>()->findNetwork(getSsid())->referenceAccessPoint()->uni();
            break;
        }
    }
    return path;
}

QString WirelessConnectionSettingsInterface::getNextHotspotName(QString p_name)
{
    QString retVal;
    // Get available connections
    QStringList names;
    for(NetworkManager::Connection::Ptr con : NetworkManager::listConnections()){
        names.append(con->name());
    }
    for(int i=1; i<=100; ++i) {
        QString tmpName = p_name + " " + QString::number(i);
        // Name free?
        if(!names.contains(tmpName)) {
            retVal = tmpName;
            break;
        }
    }
    return retVal;
}

QString WirelessConnectionSettingsInterface::getSsid()
{
    if(m_settings == NULL) return "";
    return m_settings->setting(NetworkManager::Setting::SettingType::Wireless).staticCast<NetworkManager::WirelessSetting>()->ssid();
    return "";
}

void WirelessConnectionSettingsInterface::setSsid(QString p_ssid)
{
    if(m_settings != NULL){
        m_settings->setting(NetworkManager::Setting::SettingType::Wireless).staticCast<NetworkManager::WirelessSetting>()->setSsid(QByteArray(p_ssid.toUtf8()));
        emit devicesChanged();
        emit ssidChanged();
    }
}

QString WirelessConnectionSettingsInterface::getPassword()
{
    QString password = "";
    if(m_connection!=NULL){
        QDBusPendingReply<NMVariantMapMap> map=m_connection->secrets("802-11-wireless-security");
        password=map.value()["802-11-wireless-security"]["psk"].toString();
    }
    return password;
}

void WirelessConnectionSettingsInterface::setPassword(QString p_password)
{
    if(m_settings != NULL){
        m_settings->setting(NetworkManager::Setting::SettingType::WirelessSecurity).staticCast<NetworkManager::WirelessSecuritySetting>()->setPsk(p_password);
        QVariantMap map = m_settings->setting(NetworkManager::Setting::SettingType::WirelessSecurity).staticCast<NetworkManager::WirelessSecuritySetting>()->secretsToMap();
        map["psk"]=p_password;
        m_settings->setting(NetworkManager::Setting::SettingType::WirelessSecurity).staticCast<NetworkManager::WirelessSecuritySetting>()->secretsFromMap(map);
        map = m_settings->setting(NetworkManager::Setting::SettingType::WirelessSecurity).staticCast<NetworkManager::WirelessSecuritySetting>()->secretsToMap();
        emit passwordChanged();
    }
}

QString WirelessConnectionSettingsInterface::getMode()
{
    if(m_settings == NULL) return "CLIENT";
    NetworkManager::WirelessSetting::NetworkMode mode = m_settings->setting(NetworkManager::Setting::SettingType::Wireless).staticCast<NetworkManager::WirelessSetting>()->mode();
    switch(mode){
    case NetworkManager::WirelessSetting::NetworkMode::Infrastructure:
        return "CLIENT";
        break;
    case NetworkManager::WirelessSetting::NetworkMode::Ap:
        return "HOTSPOT";
        break;
    case NetworkManager::WirelessSetting::NetworkMode::Adhoc:
        return "";
        break;
    }
    return "";

}

void WirelessConnectionSettingsInterface::setMode(QString p_mode)
{
    if(m_settings != NULL){
        if(p_mode == "CLIENT"){
            m_settings->setting(NetworkManager::Setting::SettingType::Wireless).staticCast<NetworkManager::WirelessSetting>()->setMode(NetworkManager::WirelessSetting::NetworkMode::Infrastructure);
            m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>()->setMethod(NetworkManager::Ipv4Setting::ConfigMethod::Automatic);
        }else if(p_mode == "HOTSPOT"){
            m_settings->setting(NetworkManager::Setting::SettingType::Wireless).staticCast<NetworkManager::WirelessSetting>()->setMode(NetworkManager::WirelessSetting::NetworkMode::Ap);
            m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>()->setMethod(NetworkManager::Ipv4Setting::ConfigMethod::Shared);
        }
    }
}

bool WirelessConnectionSettingsInterface::getAutoconnect()
{
    bool retVal=false;
    if(m_settings != NULL){
        retVal=m_settings->autoconnect();
    }
    return retVal;
}

void WirelessConnectionSettingsInterface::setAutoconnect(bool p_autoconnect)
{
    if(m_settings != NULL){
        m_settings->setAutoconnect(p_autoconnect);
        emit autoconnectChanged();
    }
}
