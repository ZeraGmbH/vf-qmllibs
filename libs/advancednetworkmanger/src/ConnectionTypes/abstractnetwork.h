#ifndef ABSTRACTNETWORK_H
#define ABSTRACTNETWORK_H

#include "connectionlist.h"
#include "devicemanager.h"
#include <NetworkManagerQt/ActiveConnection>
#include <NetworkManagerQt/Connection>
#include <NetworkManagerQt/ConnectionSettings>
#include <NetworkManagerQt/AccessPoint>
#include <NetworkManagerQt/Manager>
#include <NetworkManagerQt/Settings>
#include <NetworkManagerQt/Setting>
#include <NetworkManagerQt/Ipv4Setting>
#include <NetworkManagerQt/Ipv6Setting>
#include <QMap>
#include <QList>

class ConStruct{
public:
    QVariant metaData;
    QVariant con;
    QList<QMetaObject::Connection> qtCons;
};

class DevStruct{
public:
    NetworkManager::Device::Ptr dev;
    QList<QMetaObject::Connection> qtCons;
};

class AconStruct{
public:
    QString path;
    QList<QMetaObject::Connection> qtCons;
};

class AbstractNetwork : public QObject
{
    Q_OBJECT
public:
    AbstractNetwork();
    virtual bool init(ConnectionList &p_list, DeviceManager &p_devManager) = 0;
public slots:
    virtual void addConnection(const QString &connection);
    virtual void removeConnection(const QString &connection);
    virtual void addDevice(NetworkManager::Device::Type p_type, QString p_device);
    virtual void removeDevice(QString p_device);

    void ipv4Change();
    void connectionActivated(const QString &p_path);
    void connectionDeactivate(const QString &p_path);

protected:
    virtual connectionItem CreateConItem(NetworkManager::Connection::Ptr p_con) = 0;
    void addAvailabelConnection(const QString &p_devPath, const QString &p_connection);
    void removeAvailabelConnection(const QString &p_devPath, const QString &p_connection);
    void addConnectionToList(NetworkManager::Connection::Ptr p_con, connectionItem conItem);
    void findAvailableConnections(QString &p_uni);
    void findStoredConnections();
    bool isConnectionActive(QString p_path);
    QString getIpv4(QString p_path);

    ConnectionList* m_list;
    QMap<QString,ConStruct> m_conList;
    QMap<QString,AconStruct> m_aConList;
    QMap<QString,DevStruct> m_devList;
    DeviceManager* m_devManager;
    NetworkManager::Device::Type m_type;
    NetworkManager::Setting::SettingType m_setType;

private:
    void update(QString path);
    void stateChangeReason(QString path, NetworkManager::ActiveConnection::State state,NetworkManager::ActiveConnection::Reason reason);
};

#endif // ABSTRACTNETWORK_H
