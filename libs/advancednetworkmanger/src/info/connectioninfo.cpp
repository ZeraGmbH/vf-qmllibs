#include "connectioninfo.h"
#include <NetworkManagerQt/Manager>

ConnectionInfo::ConnectionInfo(NetworkManager::ActiveConnection::Ptr activeConnection) :
    m_activeConnection(activeConnection)
{
    updateConnection();
}

QString ConnectionInfo::getPath() const
{
    return m_activeConnection->path();
}

QString ConnectionInfo::getDevice() const
{
    return m_device;
}

QString ConnectionInfo::getType() const
{
    return m_type;
}

static QString getConnectionTypeStr(NetworkManager::Device::Type type) {
    switch(type) {
    case NetworkManager::Device::UnknownType:
        return "unknown";
    case NetworkManager::Device::Ethernet:
        return "Ethernet";
    case NetworkManager::Device::Wifi:
        return "Wifi";
    default:
        return "other";
    };
}

bool ConnectionInfo::updateConnection()
{
    bool modified = false;
    const QStringList devices = m_activeConnection->devices();
    if(devices.size() > 0) {
        NetworkManager::Device::Ptr device = NetworkManager::findNetworkInterface(devices.at(0));
        const QString type = getConnectionTypeStr(device->type());
        modified |= setType(type);
        QString deviceName = device->interfaceName();
        modified |= setDevice(deviceName);
    }
    const NetworkManager::IpAddresses v4Adresses = m_activeConnection->ipV4Config().addresses();
    if (v4Adresses.size() > 0) {
        QString ipv4 = v4Adresses.at(0).ip().toString();
        modified |= setIpV4(ipv4);
        QString subnetmask = v4Adresses.at(0).netmask().toString();
        modified |= setSubnetMask(subnetmask);
    }
    const NetworkManager::IpAddresses v6Adresses = m_activeConnection->ipV6Config().addresses();
    if (v6Adresses.size() > 0) {
        QString ipv6 = v6Adresses.at(0).ip().toString();
        modified |= setIpV6(ipv6);
    }
    return modified;
}

const QString ConnectionInfo::getIpV4() const
{
    return getNaAdjustedValue(m_ipv4);
}

const QString ConnectionInfo::getSubnetMask() const
{
    return getNaAdjustedValue(m_subnetmask);
}

const QString ConnectionInfo::getIpV6() const
{
    return getNaAdjustedValue(m_ipv6);
}

const QString ConnectionInfo::getNaAdjustedValue(const QString &value) const
{
    if (!value.isEmpty())
        return value;
    return "N/A";
}

bool ConnectionInfo::setDevice(const QString &device)
{
    if (m_device != device) {
        m_device = device;
        return true;
    }
    return false;
}

bool ConnectionInfo::setType(const QString &typeStr)
{
    if (m_type != typeStr) {
        m_type = typeStr;
        return true;
    }
    return false;
}

bool ConnectionInfo::setIpV4(const QString &ipv4)
{
    if (m_ipv4 != ipv4) {
        m_ipv4 = ipv4;
        return true;
    }
    return false;
}

bool ConnectionInfo::setSubnetMask(const QString &subnetmask)
{
    if (m_subnetmask != subnetmask) {
        m_subnetmask = subnetmask;
        return true;
    }
    return false;
}

bool ConnectionInfo::setIpV6(const QString &ipv6)
{
    if (m_ipv6 != ipv6) {
        m_ipv6 = ipv6;
        return true;
    }
    return false;
}
