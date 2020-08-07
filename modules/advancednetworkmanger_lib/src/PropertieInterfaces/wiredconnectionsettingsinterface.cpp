#include "wiredconnectionsettingsinterface.h"

WiredConnectionSettingsInterface::WiredConnectionSettingsInterface(QObject* parent) : AbstractConnectionSettingsInterface(parent)
{
}

void WiredConnectionSettingsInterface::create()
{
    m_settings= NetworkManager::ConnectionSettings::Ptr(new NetworkManager::ConnectionSettings(NetworkManager::ConnectionSettings::ConnectionType::Wired));
    m_settings->setUuid(QUuid::createUuid().toString().remove('{').remove('}'));
    for(auto ptr : m_settings->settings()){
        ptr->setInitialized(true);
    }
    NMVariantMapMap map = m_settings->toMap();
    map.remove("802-1x");
    m_settings->fromMap(map);
    emit loadComplete();
}

QStringList WiredConnectionSettingsInterface::getDevices()
{
    NetworkManager::Device::List devList = NetworkManager::networkInterfaces();
    QStringList list;
    for(NetworkManager::Device::Ptr dev : devList) {
        if(dev->type() == NetworkManager::Device::Type::Ethernet){
            list.append(dev->interfaceName());
        }
    }
    return list;
}


QString WiredConnectionSettingsInterface::getIpv4Mode()
{
    QString ret = "";
    NetworkManager::Ipv4Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>();
    if(set != NULL) {
        switch(set->method()) {
        case NetworkManager::Ipv4Setting::ConfigMethod::Manual:
            ret= "MANUAL";
            break;
        case NetworkManager::Ipv4Setting::ConfigMethod::Automatic:
            ret= "DHCP";
            break;
        case NetworkManager::Ipv4Setting::ConfigMethod::LinkLocal:
            ret= "";
            break;
        case NetworkManager::Ipv4Setting::ConfigMethod::Shared:
            ret= "";
            break;
        case NetworkManager::Ipv4Setting::ConfigMethod::Disabled:
            ret= "DISABLED";
            break;

        }
    }
    return ret;
}

void WiredConnectionSettingsInterface::setIpv4Mode(QString p_ipv4Mode)
{
    if(m_settings != nullptr) {
        NetworkManager::Ipv4Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>();
        if(p_ipv4Mode == "DHCP") {
            set->setMethod(NetworkManager::Ipv4Setting::ConfigMethod::Automatic);
        } else if(p_ipv4Mode == "MANUAL"){
            set->setMethod(NetworkManager::Ipv4Setting::ConfigMethod::Manual);
        }
        emit ipv4ModeChanged();
    }
}

QString WiredConnectionSettingsInterface::getIpv4()
{
    NetworkManager::Ipv4Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>();
    if(set->addresses().size() > 0) {
        return set->addresses().at(0).ip().toString();
    } else {
        return "";
    }
}

void WiredConnectionSettingsInterface::setIpv4(QString p_ipv4)
{
    NetworkManager::Ipv4Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>();
    NMVariantMapList addressData=set->addressData();
    if(addressData.size()==0) {
        addressData.append(QVariantMap());
    }
    QList< NetworkManager::IpAddress > addresses=set->addresses();
    if(addresses.size()==0) {
        addresses.append(NetworkManager::IpAddress());
    }

    addressData[0]["address"]=p_ipv4;
    addresses[0].setIp(QHostAddress(p_ipv4));
    set->setAddressData(addressData);
    set->setAddresses(addresses);
    emit ipv4Changed();
}

QString WiredConnectionSettingsInterface::getIpv4Sub()
{
    NetworkManager::Ipv4Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>();
    if(set->addresses().size() > 0) {
        QNetworkAddressEntry formatAdapter;
        formatAdapter.setIp(QHostAddress(set->addressData()[0]["address"].toString()));
        formatAdapter.setPrefixLength(set->addressData()[0]["prefix"].toInt());
        return formatAdapter.netmask().toString();
    } else {
        return "";
    }
}

void WiredConnectionSettingsInterface::setIpv4Sub(QString p_ipv4Sub)
{
    if(m_settings!=nullptr) {
        NetworkManager::Ipv4Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>();
        QNetworkAddressEntry formatAdapter;
        formatAdapter.setIp(QHostAddress(set->addressData()[0]["address"].toString()));
        formatAdapter.setNetmask(QHostAddress(p_ipv4Sub));
        NMVariantMapList addressData=set->addressData();
        if(addressData.size()==0){
            addressData.append(QVariantMap());
        }
        QList< NetworkManager::IpAddress > addresses=set->addresses();
        if(addresses.size()==0){
            addresses.append(NetworkManager::IpAddress());
        }

        addressData[0]["prefix"]=formatAdapter.prefixLength();
        addresses[0].setNetmask(QHostAddress(p_ipv4Sub));
        set->setAddressData(addressData);
        set->setAddresses(addresses);
        emit ipv4SubChanged();
    }
}

QString WiredConnectionSettingsInterface::getIpv6Mode()
{
    QString ret = "";
    NetworkManager::Ipv6Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv6).staticCast<NetworkManager::Ipv6Setting>();
    if(set != NULL) {
        switch(set->method()) {
        case NetworkManager::Ipv6Setting::ConfigMethod::Manual:
            ret= "MANUAL";
            break;
        case NetworkManager::Ipv6Setting::ConfigMethod::Automatic:
            ret= "DHCP";
            break;
        case NetworkManager::Ipv6Setting::ConfigMethod::LinkLocal:
            ret= "";
            break;
        }
    }
    return ret;
}

void WiredConnectionSettingsInterface::setIpv6Mode(QString p_ipv6Mode)
{
    if(m_settings != nullptr) {
        NetworkManager::Ipv6Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv6).staticCast<NetworkManager::Ipv6Setting>();;
        if(p_ipv6Mode == "DHCP"){
            set->setMethod(NetworkManager::Ipv6Setting::ConfigMethod::Automatic);
        } else if(p_ipv6Mode == "MANUAL") {
            set->setMethod(NetworkManager::Ipv6Setting::ConfigMethod::Manual);
        }
        emit ipv6ModeChanged();
    }
}

QString WiredConnectionSettingsInterface::getIpv6()
{
    NetworkManager::Ipv6Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv6).staticCast<NetworkManager::Ipv6Setting>();;
    if(set->addresses().size() > 0) {
        return set->addresses().at(0).ip().toString();
    } else {
        return "";
    }
}

void WiredConnectionSettingsInterface::setIpv6(QString p_ipv6)
{
    NetworkManager::Ipv6Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv6Setting>();
    NMVariantMapList addressData=set->addressData();
    if(addressData.size()==0) {
        addressData.append(QVariantMap());
    }
    QList< NetworkManager::IpAddress > addresses=set->addresses();
    if(addresses.size()==0) {
        addresses.append(NetworkManager::IpAddress());
    }
    addressData[0]["address"]=p_ipv6;
    addresses[0].setIp(QHostAddress(p_ipv6));
    set->setAddressData(addressData);
    set->setAddresses(addresses);
    emit ipv6Changed();
}

QString WiredConnectionSettingsInterface::getIpv6Sub()
{
    NetworkManager::Ipv6Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv6).staticCast<NetworkManager::Ipv6Setting>();;
    if(set->addresses().size() > 0) {
        return set->addresses().at(0).netmask().toString();
    } else {
        return "";
    }
}

void WiredConnectionSettingsInterface::setIpv6Sub(QString p_ipv6Sub)
{
    if(m_settings!=nullptr) {
         NetworkManager::Ipv6Setting::Ptr set = m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv6Setting>();
         NMVariantMapList addressData=set->addressData();
         if(addressData.size()==0) {
             addressData.append(QVariantMap());
         }
         addressData[0]["prefix"]=p_ipv6Sub.toInt();
         QList< NetworkManager::IpAddress > addresses=set->addresses();
         if(addresses.size()==0) {
             addresses.append(NetworkManager::IpAddress());
         }
         addresses[0].setPrefixLength(p_ipv6Sub.toInt());
         set->setAddressData(addressData);
         set->setAddresses(addresses);
    }
}
