#include "devicemanager.h"
#include <NetworkManagerQt/Manager>


DeviceManager::DeviceManager()
{

}

void DeviceManager::init()
{
    m_devList = NetworkManager::networkInterfaces();
    for(NetworkManager::Device::Ptr dev : m_devList){
        dev->setAutoconnect(false);
    }
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
    for(NetworkManager::Device::Ptr dev : m_devList){
        if(dev->uni() == p_devicePath){
           return dev;
        }
    }
    return nullptr;
}

void DeviceManager::deviceAdded(const QString &p_uni)
{
    m_devList = NetworkManager::networkInterfaces();
    NetworkManager::Device::Ptr dev = getDevice(p_uni);
    dev->setAutoconnect(false);
    emit addDevice(dev->type(), p_uni);
}

void DeviceManager::deviceRemoved(const QString &p_uni)
{
    m_devList = NetworkManager::networkInterfaces();
    emit removeDevice(p_uni);
}


