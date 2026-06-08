#include "wiredconnectionsettingsinterface.h"
#include "netmansubsettings.h"
#include <NetworkManagerQt/Manager>
#include <QUuid>

void WiredConnectionSettingsInterface::create()
{
    m_settings = NetworkManager::ConnectionSettings::Ptr(new NetworkManager::ConnectionSettings(NetworkManager::ConnectionSettings::ConnectionType::Wired));
    m_settings->setUuid(QUuid::createUuid().toString().remove('{').remove('}'));
    for (auto ptr : m_settings->settings())
        ptr->setInitialized(true);

    NMVariantMapMap map = m_settings->toMap();
    map.remove("802-1x");
    m_settings->fromMap(map);
    m_settings->setAutoconnect(true);
    emit loadComplete();
}

QStringList WiredConnectionSettingsInterface::getDevices()
{
    NetworkManager::Device::List devList = NetworkManager::networkInterfaces();
    QStringList list;
    for (const NetworkManager::Device::Ptr &dev : devList) {
        if (dev->type() == NetworkManager::Device::Type::Ethernet)
            list.append(dev->interfaceName());
    }
    return list;
}


QString WiredConnectionSettingsInterface::getIpv4Mode()
{
    NetworkManager::Ipv4Setting::Ptr ipv4Settings = NetManSubSettings::getIpv4Settings(m_settings);
    if (ipv4Settings != nullptr) {
        switch(ipv4Settings->method()) {
        case NetworkManager::Ipv4Setting::ConfigMethod::Manual:
            return "MANUAL";
        case NetworkManager::Ipv4Setting::ConfigMethod::Automatic:
            return "AUTOMATIC";
        case NetworkManager::Ipv4Setting::ConfigMethod::Disabled:
            return "DISABLED";
        default:
            return "";
        }
    }
    return "";
}

void WiredConnectionSettingsInterface::setIpv4Mode(const QString &ipv4Mode)
{
    NetworkManager::Ipv4Setting::Ptr ipv4Settings = NetManSubSettings::getIpv4Settings(m_settings);
    if (ipv4Settings != nullptr) {
        if (ipv4Mode == "AUTOMATIC")
            ipv4Settings->setMethod(NetworkManager::Ipv4Setting::ConfigMethod::Automatic);
        else if (ipv4Mode == "MANUAL")
            ipv4Settings->setMethod(NetworkManager::Ipv4Setting::ConfigMethod::Manual);
        emit ipv4ModeChanged();
    }
}

QString WiredConnectionSettingsInterface::getIpv4()
{
    NetworkManager::Ipv4Setting::Ptr ipv4Settings = NetManSubSettings::getIpv4Settings(m_settings);
    if (ipv4Settings != nullptr) {
        if(ipv4Settings->addresses().size() > 0)
            return ipv4Settings->addresses().at(0).ip().toString();
    }
    return "";
}

void WiredConnectionSettingsInterface::setIpv4(const QString &ipv4)
{
    NetworkManager::Ipv4Setting::Ptr ipv4Settings = NetManSubSettings::getIpv4Settings(m_settings);
    if (ipv4Settings != nullptr) {
        NMVariantMapList addressData = ipv4Settings->addressData();
        if (addressData.isEmpty())
            addressData.append(QVariantMap());
        QList< NetworkManager::IpAddress > addresses = ipv4Settings->addresses();
        if (addresses.isEmpty())
            addresses.append(NetworkManager::IpAddress());

        addressData[0]["address"]=ipv4;
        addresses[0].setIp(QHostAddress(ipv4));
        ipv4Settings->setAddressData(addressData);
        ipv4Settings->setAddresses(addresses);
        emit ipv4Changed();
    }
}

QString WiredConnectionSettingsInterface::getIpv4Sub()
{
    NetworkManager::Ipv4Setting::Ptr ipv4Settings = NetManSubSettings::getIpv4Settings(m_settings);
    if (ipv4Settings != nullptr) {
        if (ipv4Settings->addresses().size() > 0) {
            QNetworkAddressEntry formatAdapter;
            formatAdapter.setIp(QHostAddress(ipv4Settings->addressData()[0]["address"].toString()));
            formatAdapter.setPrefixLength(ipv4Settings->addressData()[0]["prefix"].toInt());
            return formatAdapter.netmask().toString();
        }
    }
    return "";
}

void WiredConnectionSettingsInterface::setIpv4Sub(const QString &ipv4Sub)
{
    NetworkManager::Ipv4Setting::Ptr ipv4Settings = NetManSubSettings::getIpv4Settings(m_settings);
    if (ipv4Settings != nullptr) {
        NMVariantMapList addressData = ipv4Settings->addressData();
        if (addressData.isEmpty())
            addressData.append(QVariantMap());
        QList<NetworkManager::IpAddress> addresses = ipv4Settings->addresses();
        if (addresses.isEmpty())
            addresses.append(NetworkManager::IpAddress());

        QNetworkAddressEntry formatAdapter;
        formatAdapter.setIp(QHostAddress(ipv4Settings->addressData()[0]["address"].toString()));
        formatAdapter.setNetmask(QHostAddress(ipv4Sub));
        addressData[0]["prefix"]=formatAdapter.prefixLength();

        addresses[0].setNetmask(QHostAddress(ipv4Sub));
        ipv4Settings->setAddressData(addressData);
        ipv4Settings->setAddresses(addresses);
        emit ipv4SubChanged();
    }
}

QString WiredConnectionSettingsInterface::getIpv6Mode()
{
    NetworkManager::Ipv6Setting::Ptr ipv6Settings = NetManSubSettings::getIpv6Settings(m_settings);
    if (ipv6Settings != nullptr) {
        switch (ipv6Settings->method()) {
        case NetworkManager::Ipv6Setting::ConfigMethod::Manual:
            return "MANUAL";
        case NetworkManager::Ipv6Setting::ConfigMethod::Automatic:
            return "AUTOMATIC";
        default:
            return "";
        }
    }
    return "";
}

void WiredConnectionSettingsInterface::setIpv6Mode(const QString &ipv6Mode)
{
    NetworkManager::Ipv6Setting::Ptr ipv6Settings = NetManSubSettings::getIpv6Settings(m_settings);
    if (ipv6Settings != nullptr) {
        if (ipv6Mode == "AUTOMATIC")
            ipv6Settings->setMethod(NetworkManager::Ipv6Setting::ConfigMethod::Automatic);
        else if(ipv6Mode == "MANUAL")
            ipv6Settings->setMethod(NetworkManager::Ipv6Setting::ConfigMethod::Manual);
        emit ipv6ModeChanged();
    }
}

QString WiredConnectionSettingsInterface::getIpv6()
{
    NetworkManager::Ipv6Setting::Ptr ipv6Settings = NetManSubSettings::getIpv6Settings(m_settings);
    if (ipv6Settings != nullptr) {
        if (!ipv6Settings->addresses().isEmpty())
            return ipv6Settings->addresses().at(0).ip().toString();
    }
    return "";
}

void WiredConnectionSettingsInterface::setIpv6(const QString &ipv6)
{
    NetworkManager::Ipv6Setting::Ptr ipv6Settings = NetManSubSettings::getIpv6Settings(m_settings);
    if (ipv6Settings != nullptr) {
        NMVariantMapList addressData = ipv6Settings->addressData();
        if (addressData.isEmpty())
            addressData.append(QVariantMap());
        QList< NetworkManager::IpAddress > addresses = ipv6Settings->addresses();
        if(addresses.isEmpty())
            addresses.append(NetworkManager::IpAddress());
        addressData[0]["address"] = ipv6;
        addresses[0].setIp(QHostAddress(ipv6));
        ipv6Settings->setAddressData(addressData);
        ipv6Settings->setAddresses(addresses);
        emit ipv6Changed();
    }
}

QString WiredConnectionSettingsInterface::getIpv6Sub()
{
    NetworkManager::Ipv6Setting::Ptr ipv6Settings = NetManSubSettings::getIpv6Settings(m_settings);
    if (ipv6Settings != nullptr) {
        if (!ipv6Settings->addresses().isEmpty())
            return ipv6Settings->addresses().at(0).netmask().toString();
    }
    return "";
}

void WiredConnectionSettingsInterface::setIpv6Sub(const QString &ipv6Sub)
{
    NetworkManager::Ipv6Setting::Ptr ipv6Settings = NetManSubSettings::getIpv6Settings(m_settings);
    if (ipv6Settings != nullptr) {
         NMVariantMapList addressData = ipv6Settings->addressData();
         if (addressData.isEmpty())
             addressData.append(QVariantMap());
         addressData[0]["prefix"] = ipv6Sub.toInt();
         QList<NetworkManager::IpAddress> addresses = ipv6Settings->addresses();
         if (addresses.isEmpty())
             addresses.append(NetworkManager::IpAddress());
         addresses[0].setPrefixLength(ipv6Sub.toInt());
         ipv6Settings->setAddressData(addressData);
         ipv6Settings->setAddresses(addresses);
    }
}
