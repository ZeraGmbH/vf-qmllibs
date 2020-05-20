#ifndef WIFINETWORKS_H
#define WIFINETWORKS_H
#include <QTimer>
#include "abstractnetwork.h"
#include <NetworkManagerQt/WirelessDevice>


enum class ConClassType{NA = 0, Con, AP};


class WifiNetworks : public AbstractNetwork
{
    Q_OBJECT
public:
    WifiNetworks();
    ~WifiNetworks();
    bool init(ConnectionList  &p_list, DeviceManager &p_devManager) override;
private:
    void findAPs(QString &p_uni);
    connectionItem CreateConItem(NetworkManager::Connection::Ptr) override;

private:
    QMap<QString,int> aplist;
    QTimer *m_timer;
public slots:
    void addAccessPoint(const QString &p_uni);
    void removeAccessPoint(const QString &p_uni);
    void addConnection(const QString &connection) override;
    void removeConnection(const QString &connection) override;
    void addDevice(NetworkManager::Device::Type p_type, QString p_device) override;
    void updateSignal();
};

Q_DECLARE_METATYPE(ConClassType)

#endif // WIFINETWORKS_H
