#include "devicemanager.h"
#include <NetworkManagerQt/Manager>

DeviceManager::DeviceManager()
{
}

void DeviceManager::init()
{
    m_devList = NetworkManager::networkInterfaces();
    connect(NetworkManager::notifier(),&NetworkManager::Notifier::deviceAdded,this,&DeviceManager::deviceAdded);
    connect(NetworkManager::notifier(),&NetworkManager::Notifier::deviceRemoved,this,&DeviceManager::deviceRemoved);
}

QList<QString> DeviceManager::getDevices(NetworkManager::Device::Type p_type)
{
    QList<QString> list;

    for(NetworkManager::Device::Ptr dev : m_devList){
        if(dev->type() == p_type){
            list.append(dev->uni());
        }
    }
    return list;
}

NetworkManager::Device::Ptr DeviceManager::getDevice(QString p_devicePath)
{
    m_devList = NetworkManager::networkInterfaces();
    for(NetworkManager::Device::Ptr dev : m_devList){
        if(dev->uni() == p_devicePath){
           return dev;
        }
    }
    return nullptr;
}

NetworkManager::Device::List DeviceManager::getDevicesbyInterface(QString p_interfaceName)
{
    NetworkManager::Device::List devList;
    for(NetworkManager::Device::Ptr dev : m_devList){
        if(dev->interfaceName() == p_interfaceName){
            devList.append(dev);
        }
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
    m_devList = NetworkManager::networkInterfaces();
    NetworkManager::Device::Ptr dev = getDevice(p_uni);
    emit addDevice(dev->type(), p_uni);
}

void DeviceManager::deviceRemoved(const QString &p_uni)
{
    m_devList = NetworkManager::networkInterfaces();
    emit removeDevice(p_uni);
}
