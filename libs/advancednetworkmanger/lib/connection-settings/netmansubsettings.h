#ifndef NETMANSUBSETTINGS_H
#define NETMANSUBSETTINGS_H

#include <NetworkManagerQt/Settings>
#include <NetworkManagerQt/ConnectionSettings>
#include <NetworkManagerQt/Ipv4Setting>
#include <NetworkManagerQt/Ipv6Setting>
#include <NetworkManagerQt/WirelessSetting>
#include <NetworkManagerQt/WirelessSecuritySetting>

class NetManSubSettings
{
public:
    static NetworkManager::Ipv4Setting::Ptr getIpv4Settings(const NetworkManager::ConnectionSettings::Ptr &settings);
    static NetworkManager::Ipv6Setting::Ptr getIpv6Settings(const NetworkManager::ConnectionSettings::Ptr &settings);
    static NetworkManager::WirelessSetting::Ptr getWiressSettings(const NetworkManager::ConnectionSettings::Ptr &settings);
    static NetworkManager::WirelessSecuritySetting::Ptr getWiressSecuritySettings(const NetworkManager::ConnectionSettings::Ptr &settings);
};

#endif // NETMANSUBSETTINGS_H
