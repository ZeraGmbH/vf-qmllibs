#ifndef ABSTRACTCONNECTIONSETTINGSINTERFACE_H
#define ABSTRACTCONNECTIONSETTINGSINTERFACE_H

#include <NetworkManagerQt/Connection>
#include <NetworkManagerQt/ConnectionSettings>

class AbstractConnectionSettingsInterface : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString conName READ getConName WRITE setConName NOTIFY conNameChanged)
    Q_PROPERTY(QStringList devices READ getDevices NOTIFY devicesChanged)
    Q_PROPERTY(QString device READ getDevice WRITE setDevice NOTIFY deviceChanged)

    Q_INVOKABLE virtual void create() = 0;
    Q_INVOKABLE void load(QString p_path);
    Q_INVOKABLE void save();
    Q_INVOKABLE virtual void saveAndActivate(const QString &p_devUni, const QString &p_apPath);
    Q_INVOKABLE void discard();
    Q_INVOKABLE virtual QString getDevicePath(const QString &p_interfaceName);
    Q_INVOKABLE QString getHostName();

    virtual QStringList getDevices();
    virtual QString getDevice();
    virtual void setDevice(QString &device);
    QString getConName();
    void setConName(QString p_conName);
signals:
    void conNameChanged();
    void loadComplete();
    void devicesChanged();
    void deviceChanged();

protected:
    NetworkManager::Connection::Ptr m_connection;
    NetworkManager::ConnectionSettings::Ptr m_settings;
    NMVariantMapMap m_connectionMap;
};

#endif // ABSTRACTCONNECTIONSETTINGSINTERFACE_H
