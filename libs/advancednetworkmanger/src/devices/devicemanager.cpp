#include "devicemanager.h"
#include <NetworkManagerQt/Manager>

DeviceManager::DeviceManager()
{
    connect(NetworkManager::notifier(), &NetworkManager::Notifier::deviceAdded,
            this, &DeviceManager::onDeviceAdded);
    connect(NetworkManager::notifier(), &NetworkManager::Notifier::deviceRemoved,
            this, &DeviceManager::onDeviceRemoved);

    const NetworkManager::Device::List netManDevices = NetworkManager::networkInterfaces();
    for (const NetworkManager::Device::Ptr &netManDevice : netManDevices)
        QMetaObject::invokeMethod(this,
                                  "onDeviceAdded",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, netManDevice->uni()));
}

QStringList DeviceManager::getDevices(NetworkManager::Device::Type netManDeviceType)
{
    QStringList list;
    for(NetworkManager::Device::Ptr netManDevice : NetworkManager::networkInterfaces()) {
        if(netManDevice->type() == netManDeviceType)
            list.append(netManDevice->uni());
    }
    return list;
}

NetworkManager::Device::Ptr DeviceManager::getDevice(const QString &devicePath)
{
    for(NetworkManager::Device::Ptr netManDevice : NetworkManager::networkInterfaces()) {
        if(netManDevice->uni() == devicePath)
           return netManDevice;
    }
    return nullptr;
}

NetworkManager::Device::List DeviceManager::getDevicesbyInterface(const QString &interfaceName)
{
    NetworkManager::Device::List devList;
    for(NetworkManager::Device::Ptr dev : NetworkManager::networkInterfaces()) {
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

void DeviceManager::onDeviceAdded(const QString &uni)
{
    if (!m_deviceUnisAdded.contains(uni)) {
        m_deviceUnisAdded.insert(uni);
        NetworkManager::Device::Ptr dev = getDevice(uni);
        emit sigAddDevice(dev->type(), uni);
    }
}

void DeviceManager::onDeviceRemoved(const QString &uni)
{
    m_deviceUnisAdded.remove(uni);
    emit sigRemoveDevice(uni);
}
