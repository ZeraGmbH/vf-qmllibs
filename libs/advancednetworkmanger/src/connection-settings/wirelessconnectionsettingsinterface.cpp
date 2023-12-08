#include "wirelessconnectionsettingsinterface.h"
#include <QUuid>
#include "NetworkManagerQt/WirelessDevice"
#include <NetworkManagerQt/Settings>
#include "NetworkManagerQt/WirelessSetting"
#include <NetworkManagerQt/WirelessSecuritySetting>
#include <NetworkManagerQt/Ipv4Setting>
#include <NetworkManagerQt/Ipv6Setting>

void WirelessConnectionSettingsInterface::saveAndActivate(const QString &p_devUni,const QString &p_apPath)
{
    if(m_settings != nullptr) {
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
    m_settings->setAutoconnect(true);
    emit loadComplete();
}

QStringList WirelessConnectionSettingsInterface::getDevices()
{   
    NetworkManager::Device::List devList = NetworkManager::networkInterfaces();
    QStringList list;
    for(const NetworkManager::Device::Ptr &dev : devList){
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
    for(const NetworkManager::Device::Ptr &dev : devList){
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
    for(const NetworkManager::Connection::Ptr &con : NetworkManager::listConnections()){
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
    if(m_settings != nullptr)
        return m_settings->setting(NetworkManager::Setting::SettingType::Wireless).staticCast<NetworkManager::WirelessSetting>()->ssid();
    return "";
}

void WirelessConnectionSettingsInterface::setSsid(QString p_ssid)
{
    if(m_settings != nullptr) {
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
    if(m_settings != nullptr) {
        NetworkManager::WirelessSecuritySetting::Ptr settingSecurity =
            m_settings->setting(NetworkManager::Setting::SettingType::WirelessSecurity).staticCast<NetworkManager::WirelessSecuritySetting>();

        settingSecurity->setPsk(p_password);
        QVariantMap map = settingSecurity->secretsToMap();
        map["psk"] = p_password;
        settingSecurity->secretsFromMap(map);
        map = settingSecurity->secretsToMap();
        emit passwordChanged();
    }
}

QString WirelessConnectionSettingsInterface::getMode()
{
    if(m_settings == nullptr)
        return "CLIENT";
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
    if(m_settings != nullptr) {
        NetworkManager::WirelessSetting::Ptr settingsWireless = m_settings->setting(NetworkManager::Setting::SettingType::Wireless).staticCast<NetworkManager::WirelessSetting>();
        NetworkManager::Ipv4Setting::Ptr setttingsIpv4 = m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>();
        if(p_mode == "CLIENT"){
            settingsWireless->setMode(NetworkManager::WirelessSetting::NetworkMode::Infrastructure);
            setttingsIpv4->setMethod(NetworkManager::Ipv4Setting::ConfigMethod::Automatic);
        }
        else if(p_mode == "HOTSPOT") {
            settingsWireless->setMode(NetworkManager::WirelessSetting::NetworkMode::Ap);
            settingsWireless->setSecurity("802-11-wireless-security");
            setttingsIpv4->setMethod(NetworkManager::Ipv4Setting::ConfigMethod::Shared);

            if(setttingsIpv4->addresses().count() == 0) {
                NetworkManager::IpAddress defaultAddress;
                // For the sake of WinSAM scripts
                // https://github.com/ZeraGmbH/winsam-scripts/blob/exe-api/Readout/SCPI/SCPI.inc
                defaultAddress.setIp(QHostAddress("192.168.32.14"));
                defaultAddress.setNetmask(QHostAddress("255.255.255.0"));
                setttingsIpv4->setAddresses(QList<NetworkManager::IpAddress>() << defaultAddress);
            }
        }
    }
}

bool WirelessConnectionSettingsInterface::getAutoconnect()
{
    bool retVal = false;
    if(m_settings != nullptr)
        retVal=m_settings->autoconnect();
    return retVal;
}

void WirelessConnectionSettingsInterface::setAutoconnect(bool p_autoconnect)
{
    if(m_settings != nullptr) {
        m_settings->setAutoconnect(p_autoconnect);
        emit autoconnectChanged();
    }
}

QString WirelessConnectionSettingsInterface::getIpv4()
{
    if(m_settings != nullptr) {
        NetworkManager::Ipv4Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>();
        if(set->addresses().size() > 0) {
            return set->addresses().at(0).ip().toString();
        }
    }
    return "";
}

void WirelessConnectionSettingsInterface::setIpv4(QString p_ipv4)
{
    if(m_settings != nullptr) {
        NetworkManager::Ipv4Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>();
        NMVariantMapList addressData=set->addressData();
        if(addressData.size()==0) {
            addressData.append(QVariantMap());
        }
        QList< NetworkManager::IpAddress > addresses=set->addresses();
        if(addresses.size()==0) {
            addresses.append(NetworkManager::IpAddress());
        }

        addresses[0].setNetmask(QHostAddress("255.255.255.0"));
        addresses[0].setIp(QHostAddress(p_ipv4));
        set->setAddressData(addressData);
        set->setAddresses(addresses);
        emit ipv4Changed();
    }
}
