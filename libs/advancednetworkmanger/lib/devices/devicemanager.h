#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <NetworkManagerQt/Device>
#include <NetworkManagerQt/Manager>

class DeviceManager : public QObject
{
    Q_OBJECT
public:
    DeviceManager();

    QStringList getDevices(NetworkManager::Device::Type netManDeviceType);
    NetworkManager::Device::Ptr getDevice(const QString &devicePath);
    NetworkManager::Device::List getDevicesbyInterface(const QString &interfaceName);

    static bool isLocalHost(const QString &interfaceName);
    static bool isLocalHost(NetworkManager::Device::Ptr device);
    static bool isLocalHost(NetworkManager::ActiveConnection::Ptr activeConnection);
signals:
    void sigAddDevice(NetworkManager::Device::Type netManDevType, const QString &uni);
    void sigRemoveDevice(const QString &uni);

private slots:
    void onDeviceAdded(const QString &uni);
    void onDeviceRemoved(const QString &uni);
private:
    QSet<QString> m_deviceUnisAdded;
};

#endif // DEVICEMANAGER_H
