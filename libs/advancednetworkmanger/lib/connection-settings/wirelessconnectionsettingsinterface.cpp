#include "wirelessconnectionsettingsinterface.h"
#include "netmansubsettings.h"
#include "NetworkManagerQt/WirelessDevice"
#include <QUuid>

void WirelessConnectionSettingsInterface::saveAndActivate(const QString &devUni, const QString &apPath)
{
    if(m_settings != nullptr) {
        NMVariantMapMap map = m_settings->toMap();
        NetworkManager::Connection::Ptr netManConnection = NetworkManager::findConnection(apPath);
        if (netManConnection == nullptr)
            NetworkManager::addAndActivateConnection(map, devUni, m_smartConnectPath);
        else
            NetworkManager::addAndActivateConnection(map, devUni, "");
        m_settings.clear();
        if (netManConnection != nullptr)
            netManConnection->remove();
    }
}

void WirelessConnectionSettingsInterface::create()
{
    m_settings = NetworkManager::ConnectionSettings::Ptr(new NetworkManager::ConnectionSettings(NetworkManager::ConnectionSettings::ConnectionType::Wireless));
    m_settings->setUuid(QUuid::createUuid().toString().remove('{').remove('}'));
    NetworkManager::WirelessSecuritySetting::Ptr wirelessSecuritySettings = NetManSubSettings::getWiressSecuritySettings(m_settings);
    wirelessSecuritySettings->setKeyMgmt(NetworkManager::WirelessSecuritySetting::KeyMgmt::WpaPsk);
    for (auto ptr : m_settings->settings())
        ptr->setInitialized(true);
    m_settings->setZone("trusted");
    NMVariantMapMap map = m_settings->toMap();
    map.remove("802-1x");
    m_settings->fromMap(map);
    m_settings->setAutoconnect(true);
    emit loadComplete();
}

QStringList WirelessConnectionSettingsInterface::getDevices()
{   
    const NetworkManager::Device::List devList = NetworkManager::networkInterfaces();
    QStringList list;
    for(const NetworkManager::Device::Ptr &dev : devList) {
        if(dev->type() == NetworkManager::Device::Type::Wifi)
            if(dev.staticCast<NetworkManager::WirelessDevice>()->findNetwork(getSsid()) != nullptr)
                list.append(dev->interfaceName());
    }
    return list;
}

QString WirelessConnectionSettingsInterface::getDevicePath(const QString &interfaceName)
{
    QString path;
    const NetworkManager::Device::List devList = NetworkManager::networkInterfaces();
    for (const NetworkManager::Device::Ptr &dev : devList){
        if (dev->interfaceName() == interfaceName) {
            path=dev->uni();
            m_smartConnectPath = dev.staticCast<NetworkManager::WirelessDevice>()->findNetwork(getSsid())->referenceAccessPoint()->uni();
            break;
        }
    }
    return path;
}

QString WirelessConnectionSettingsInterface::getNextHotspotName(const QString &name)
{
    QStringList namesUsed;
    const NetworkManager::Connection::List connections = NetworkManager::listConnections();
    for (const NetworkManager::Connection::Ptr &con : connections)
        namesUsed.append(con->name());

    for (int i=1; i<=100; ++i) {
        QString tmpName = name + " " + QString::number(i);
        // Name free?
        if (!namesUsed.contains(tmpName))
            return tmpName;
    }
    return "";
}

QString WirelessConnectionSettingsInterface::getSsid()
{
    NetworkManager::WirelessSetting::Ptr wirelessSettings = NetManSubSettings::getWiressSettings(m_settings);
    if(wirelessSettings != nullptr)
        return wirelessSettings->ssid();
    return "";
}

void WirelessConnectionSettingsInterface::setSsid(const QString &ssid)
{
    NetworkManager::WirelessSetting::Ptr wirelessSettings = NetManSubSettings::getWiressSettings(m_settings);
    if (wirelessSettings != nullptr) {
        wirelessSettings->setSsid(QByteArray(ssid.toUtf8()));
        emit devicesChanged();
        emit ssidChanged();
    }
}

QString WirelessConnectionSettingsInterface::getPassword()
{
    QString password;
    if (m_connection != nullptr) {
        QDBusPendingReply<NMVariantMapMap> map = m_connection->secrets("802-11-wireless-security");
        password = map.value()["802-11-wireless-security"]["psk"].toString();
    }
    return password;
}

void WirelessConnectionSettingsInterface::setPassword(const QString &password)
{
    NetworkManager::WirelessSecuritySetting::Ptr wirelessSecuritySettings = NetManSubSettings::getWiressSecuritySettings(m_settings);
    if (wirelessSecuritySettings != nullptr) {
        wirelessSecuritySettings->setPsk(password);
        QVariantMap map = wirelessSecuritySettings->secretsToMap();
        map["psk"] = password;
        wirelessSecuritySettings->secretsFromMap(map);
        map = wirelessSecuritySettings->secretsToMap();
        emit passwordChanged();
    }
}

QString WirelessConnectionSettingsInterface::getMode()
{
    NetworkManager::WirelessSetting::Ptr wirelessSettings = NetManSubSettings::getWiressSettings(m_settings);
    if (wirelessSettings == nullptr)
        return "CLIENT";
    NetworkManager::WirelessSetting::NetworkMode mode = wirelessSettings->mode();
    switch(mode){
    case NetworkManager::WirelessSetting::NetworkMode::Infrastructure:
        return "CLIENT";
    case NetworkManager::WirelessSetting::NetworkMode::Ap:
        return "HOTSPOT";
    case NetworkManager::WirelessSetting::NetworkMode::Adhoc:
        return "";
    }
    return "";

}

void WirelessConnectionSettingsInterface::setMode(const QString &mode)
{
    NetworkManager::WirelessSetting::Ptr wirelessSettings = NetManSubSettings::getWiressSettings(m_settings);
    NetworkManager::Ipv4Setting::Ptr ipV4Settings = NetManSubSettings::getIpv4Settings(m_settings);
    if (wirelessSettings != nullptr && ipV4Settings != nullptr) {
        if(mode == "CLIENT") {
            wirelessSettings->setMode(NetworkManager::WirelessSetting::NetworkMode::Infrastructure);
            ipV4Settings->setMethod(NetworkManager::Ipv4Setting::ConfigMethod::Automatic);
        }
        else if(mode == "HOTSPOT") {
            wirelessSettings->setMode(NetworkManager::WirelessSetting::NetworkMode::Ap);
            wirelessSettings->setSecurity("802-11-wireless-security");
            ipV4Settings->setMethod(NetworkManager::Ipv4Setting::ConfigMethod::Shared);

            if(ipV4Settings->addresses().isEmpty()) {
                NetworkManager::IpAddress defaultAddress;
                // For the sake of WinSAM scripts
                // https://github.com/ZeraGmbH/winsam-scripts/blob/exe-api/Readout/SCPI/SCPI.inc
                defaultAddress.setIp(QHostAddress("192.168.32.14"));
                defaultAddress.setNetmask(QHostAddress("255.255.255.0"));
                ipV4Settings->setAddresses(QList<NetworkManager::IpAddress>() << defaultAddress);
            }
        }
    }
}

bool WirelessConnectionSettingsInterface::getAutoconnect()
{
    if (m_settings == nullptr)
        return false;
    return m_settings->autoconnect();
}

void WirelessConnectionSettingsInterface::setAutoconnect(bool autoconnect)
{
    if (m_settings != nullptr) {
        m_settings->setAutoconnect(autoconnect);
        emit autoconnectChanged();
    }
}

QString WirelessConnectionSettingsInterface::getIpv4()
{
    NetworkManager::Ipv4Setting::Ptr ipV4Settings = NetManSubSettings::getIpv4Settings(m_settings);
    if (ipV4Settings == nullptr)
        return "";
    if (ipV4Settings->addresses().isEmpty())
        return "";
    return ipV4Settings->addresses().at(0).ip().toString();
}

void WirelessConnectionSettingsInterface::setIpv4(const QString &ipv4)
{
    NetworkManager::Ipv4Setting::Ptr ipV4Settings = NetManSubSettings::getIpv4Settings(m_settings);
    if (ipV4Settings != nullptr) {
        NMVariantMapList addressData = ipV4Settings->addressData();
        if(addressData.isEmpty())
            addressData.append(QVariantMap());
        QList< NetworkManager::IpAddress > addresses = ipV4Settings->addresses();
        if(addresses.isEmpty())
            addresses.append(NetworkManager::IpAddress());

        addresses[0].setNetmask(QHostAddress("255.255.255.0"));
        addresses[0].setIp(QHostAddress(ipv4));
        ipV4Settings->setAddressData(addressData);
        ipV4Settings->setAddresses(addresses);
        emit ipv4Changed();
    }
}
