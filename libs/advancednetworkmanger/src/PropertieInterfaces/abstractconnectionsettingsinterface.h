#ifndef ABSTRACTCONNECTIONSETTINGSINTERFACE_H
#define ABSTRACTCONNECTIONSETTINGSINTERFACE_H

#include <QObject>

#include <QLatin1String>

#include <NetworkManagerQt/ActiveConnection>
#include <NetworkManagerQt/Connection>
#include <NetworkManagerQt/ConnectionSettings>
#include <NetworkManagerQt/Manager>
#include <NetworkManagerQt/Settings>


#include <NetworkManagerQt/Setting>
#include <NetworkManagerQt/Ipv4Setting>
#include <NetworkManagerQt/Ipv6Setting>

#include <QtCore/QUuid>
#include <QQueue>

#include <NetworkManagerQt/Utils>

#include <iostream>

class AbstractConnectionSettingsInterface : public QObject
{
     Q_OBJECT

    Q_PROPERTY(QString conName READ getConName WRITE setConName NOTIFY conNameChanged)
    Q_PROPERTY(QStringList devices READ getDevices NOTIFY devicesChanged)
    Q_PROPERTY(QString device READ getDevice WRITE setDevice NOTIFY deviceChanged)
public:
    AbstractConnectionSettingsInterface(QObject *parent = nullptr);
    Q_INVOKABLE void load(QString p_path);
    Q_INVOKABLE virtual void create();
    Q_INVOKABLE void save();
    Q_INVOKABLE virtual void saveAndActivate(const QString &p_devUni, const QString &p_apPath);
    Q_INVOKABLE void discard();


    virtual QStringList getDevices();
    Q_INVOKABLE virtual QString getDevicePath(const QString &p_interfaceName);

    Q_INVOKABLE QString getHostName();

    virtual QString getDevice();
    virtual void setDevice(QString &device);

    QString getConName();
    void setConName(QString p_conName);

protected:
    NetworkManager::Connection::Ptr m_connection;
    NetworkManager::ConnectionSettings::Ptr m_settings;
    NMVariantMapMap m_connectionMap;

signals:
    void conNameChanged();
    void loadComplete();
    void devicesChanged();
    void deviceChanged();



};

#endif // ABSTRACTCONNECTIONSETTINGSINTERFACE_H
