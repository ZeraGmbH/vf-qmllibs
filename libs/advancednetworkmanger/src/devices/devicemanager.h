#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QList>
#include <NetworkManagerQt/Device>
#include <NetworkManagerQt/Manager>
#include <QObject>

class DeviceManager : public  QObject
{
    Q_OBJECT
public:
    DeviceManager();
    void init();
    QList<QString> getDevices(NetworkManager::Device::Type p_type);
    QList<QString> getDevices();
    NetworkManager::Device::Ptr getDevice(QString p_devicePath);
    NetworkManager::Device::List getDevicesbyInterface(QString p_interfaceName);
    static bool isLocalHost(const QString &connectionPath);
private:
    NetworkManager::Device::List m_devList;
public slots:
    void deviceAdded(const QString &p_uni);
    void deviceRemoved(const QString &p_uni);
    //void StateChanged(QString p_path,NetworkManager::Device::State newstate, NetworkManager::Device::State oldstate, NetworkManager::Device::StateChangeReason reason);

signals:
    void addDevice(NetworkManager::Device::Type p_type, QString p_devicePath);
    void removeDevice(QString p_devicePath);
};

#endif // DEVICEMANAGER_H
