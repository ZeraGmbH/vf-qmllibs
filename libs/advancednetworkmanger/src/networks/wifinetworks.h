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
    bool init(std::shared_ptr<ConnectionList> connList, std::shared_ptr<DeviceManager> devManager) override;
private:
    void findAPs(QString &p_uni);
    ConnectionItem CreateConItem(NetworkManager::Connection::Ptr) override;

private:
    QMap<QString,QString> m_apList;
    QTimer *m_timer;
public slots:
    void addAccessPoint(const QString &p_devPath, const QString &p_uni);
    void removeAccessPoint(const QString &p_devPath, const QString &p_uni);
    void addConnection(const QString &connection) override;
    void removeConnection(const QString &connection) override;
    void addDevice(NetworkManager::Device::Type p_type, QString p_device) override;
    void onGetSignalStrength();
    void stateChanged(NetworkManager::Device::Ptr dev,NetworkManager::Device::State newstate, NetworkManager::Device::State oldstate, NetworkManager::Device::StateChangeReason reason);
signals:
    void authFailed(const QString &name,const QString &path,const QString &device);
};

Q_DECLARE_METATYPE(ConClassType)

#endif // WIFINETWORKS_H
