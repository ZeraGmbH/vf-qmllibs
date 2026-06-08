#include "netmansubsettings.h"

NetworkManager::Ipv4Setting::Ptr NetManSubSettings::getIpV4Settings(const NetworkManager::ConnectionSettings::Ptr &settings)
{
    if (settings != nullptr)
        return settings->setting(NetworkManager::Setting::SettingType::Ipv4).dynamicCast<NetworkManager::Ipv4Setting>();
    return nullptr;
}

NetworkManager::Ipv6Setting::Ptr NetManSubSettings::getIpV6Settings(const NetworkManager::ConnectionSettings::Ptr &settings)
{
    if (settings != nullptr)
        return settings->setting(NetworkManager::Setting::SettingType::Ipv6).dynamicCast<NetworkManager::Ipv6Setting>();
    return nullptr;
}

NetworkManager::WirelessSetting::Ptr NetManSubSettings::getWiressSettings(const NetworkManager::ConnectionSettings::Ptr &settings)
{
    if (settings != nullptr)
        return settings->setting(NetworkManager::Setting::SettingType::Wireless).dynamicCast<NetworkManager::WirelessSetting>();
    return nullptr;
}

NetworkManager::WirelessSecuritySetting::Ptr NetManSubSettings::getWiressSecuritySettings(const NetworkManager::ConnectionSettings::Ptr &settings)
{
    if (settings != nullptr)
        return settings->setting(NetworkManager::Setting::SettingType::WirelessSecurity).dynamicCast<NetworkManager::WirelessSecuritySetting>();
    return nullptr;
}
