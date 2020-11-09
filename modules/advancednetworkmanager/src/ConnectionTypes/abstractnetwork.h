#ifndef ABSTRACTNETWORK_H
#define ABSTRACTNETWORK_H

#include "connectionlist.h"
#include "connectionmodel.h"
#include "devicemanager.h"

#include <QObject>
#include <QMap>
#include <QList>


#include <NetworkManagerQt/ActiveConnection>
#include <NetworkManagerQt/Connection>
#include <NetworkManagerQt/ConnectionSettings>
#include <NetworkManagerQt/AccessPoint>
#include <NetworkManagerQt/Manager>
#include <NetworkManagerQt/Settings>


#include <NetworkManagerQt/Setting>
#include <NetworkManagerQt/Ipv4Setting>
#include <NetworkManagerQt/Ipv6Setting>




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
protected:
    virtual void connectionActivated(const QString &p_path);
    virtual void connectionDeactivate(const QString &p_path);
    virtual void addConnectionToList(NetworkManager::Connection::Ptr p_con, connectionItem conItem);
    virtual void findAvailableConnections(QString &p_uni);
    virtual void findStoredConnections();
    virtual connectionItem CreateConItem(NetworkManager::Connection::Ptr p_con);
    virtual bool isConnectionActive(QString p_path);
protected:
    ConnectionList* m_list;
    QMap<QString,ConStruct> m_conList;
    QMap<QString,AconStruct> m_aConList;
    QMap<QString,DevStruct> m_devList;
    DeviceManager* m_devManager;
    NetworkManager::Device::Type m_type;
    NetworkManager::Setting::SettingType m_setType;

public slots:
    virtual void addConnection(const QString &connection);
    virtual void removeConnection(const QString &connection);
    virtual void addAvailabelConnection(const QString &p_devPath, const QString &p_connection);
    virtual void removeAvailabelConnection(const QString &p_devPath, const QString &p_connection);
    virtual void addDevice(NetworkManager::Device::Type p_type, QString p_device);
    virtual void removeDevice(QString p_device);
    virtual void update(QString path);
    void stateChangeReason(QString path, NetworkManager::ActiveConnection::State state,NetworkManager::ActiveConnection::Reason reason);
};

#endif // ABSTRACTNETWORK_H
