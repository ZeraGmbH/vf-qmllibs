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

private:
    NetworkManager::Device::List m_devList;
public slots:
    void deviceAdded(const QString &p_uni);
    void deviceRemoved(const QString &p_uni);
signals:
    void addDevice(NetworkManager::Device::Type p_type, QString p_devicePath);
    void removeDevice(QString p_devicePath);
};

#endif // DEVICEMANAGER_H
