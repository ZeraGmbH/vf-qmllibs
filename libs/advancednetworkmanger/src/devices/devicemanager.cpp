#include "devicemanager.h"
#include <NetworkManagerQt/Manager>

DeviceManager::DeviceManager()
{
}

void DeviceManager::init()
{
    m_netManDeviceList = NetworkManager::networkInterfaces();
    connect(NetworkManager::notifier(),&NetworkManager::Notifier::deviceAdded,this,&DeviceManager::deviceAdded);
    connect(NetworkManager::notifier(),&NetworkManager::Notifier::deviceRemoved,this,&DeviceManager::deviceRemoved);
}

QStringList DeviceManager::getDevices(NetworkManager::Device::Type netManDeviceType)
{
    QStringList list;
    for(NetworkManager::Device::Ptr netManDevice : m_netManDeviceList) {
        if(netManDevice->type() == netManDeviceType)
            list.append(netManDevice->uni());
    }
    return list;
}

NetworkManager::Device::Ptr DeviceManager::getDevice(const QString &devicePath)
{
    m_netManDeviceList = NetworkManager::networkInterfaces();
    for(NetworkManager::Device::Ptr netManDevice : m_netManDeviceList) {
        if(netManDevice->uni() == devicePath)
           return netManDevice;
    }
    return nullptr;
}

NetworkManager::Device::List DeviceManager::getDevicesbyInterface(const QString &interfaceName)
{
    NetworkManager::Device::List devList;
    for(NetworkManager::Device::Ptr dev : m_netManDeviceList) {
        if(dev->interfaceName() == interfaceName)
            devList.append(dev);
    }
    return devList;
}

bool DeviceManager::isLocalHost(const QString &interfaceName)
{
    QString upperInterfaceName = interfaceName.toUpper();
    return upperInterfaceName == "LO";
}

bool DeviceManager::isLocalHost(NetworkManager::Device::Ptr device)
{
    return isLocalHost(device->interfaceName());
}

bool DeviceManager::isLocalHost(NetworkManager::ActiveConnection::Ptr activeConnection)
{
    if (activeConnection) {
        if (activeConnection->devices().size() > 0) {
            NetworkManager::Device::Ptr device = NetworkManager::findNetworkInterface(activeConnection->devices().at(0));
            return isLocalHost(device);
        }
    }
    return false;
}

void DeviceManager::deviceAdded(const QString &p_uni)
{
    m_netManDeviceList = NetworkManager::networkInterfaces();
    NetworkManager::Device::Ptr dev = getDevice(p_uni);
    emit addDevice(dev->type(), p_uni);
}

void DeviceManager::deviceRemoved(const QString &p_uni)
{
    m_netManDeviceList = NetworkManager::networkInterfaces();
    emit removeDevice(p_uni);
}
