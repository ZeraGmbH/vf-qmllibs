#ifndef WIRELESSCONNECTIONSETTINGSINTERFACE_H
#define WIRELESSCONNECTIONSETTINGSINTERFACE_H

#include <QObject>
#include "abstractconnectionsettingsinterface.h"
#include <NetworkManagerQt/WirelessSecuritySetting>

class WirelessConnectionSettingsInterface : public AbstractConnectionSettingsInterface
{
    Q_OBJECT

    Q_PROPERTY(QString ssid READ getSsid WRITE setSsid NOTIFY ssidChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString mode READ getMode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(bool autoconnect READ getAutoconnect WRITE setAutoconnect NOTIFY devicesChanged)
    Q_PROPERTY(QStringList devices READ getDevices NOTIFY devicesChanged)

public:
    WirelessConnectionSettingsInterface(QObject *parent = nullptr);

    Q_INVOKABLE void saveAndActivate(const QString &p_devUni,const QString &p_apPath) override;

    Q_INVOKABLE void create() override;
    QStringList getDevices() override;
    Q_INVOKABLE QString getDevicePath(const QString &p_interfaceName) override;

    Q_INVOKABLE QString getNextHotspotName(QString p_name);

    QString getSsid();
    void setSsid(QString p_ssid);

    QString getPassword();
    void setPassword(QString p_password);

    QString getMode();
    void setMode(QString p_mode);

    bool getAutoconnect();
    void setAutoconnect(bool p_autoconnect);
protected:
    QString m_smartConnectPath;
signals:
    void ssidChanged();
    void passwordChanged();
    void modeChanged();
    void devicesChanged();
    void autoconnectChanged();

};

#endif // WIRELESSCONNECTIONSETTINGSINTERFACE_H
