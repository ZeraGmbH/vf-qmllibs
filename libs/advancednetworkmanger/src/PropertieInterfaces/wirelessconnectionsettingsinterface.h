#ifndef WIRELESSCONNECTIONSETTINGSINTERFACE_H
#define WIRELESSCONNECTIONSETTINGSINTERFACE_H

#include "abstractconnectionsettingsinterface.h"

class WirelessConnectionSettingsInterface : public AbstractConnectionSettingsInterface
{
    Q_OBJECT
public:
    Q_PROPERTY(QString ssid READ getSsid WRITE setSsid NOTIFY ssidChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString mode READ getMode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(bool autoconnect READ getAutoconnect WRITE setAutoconnect NOTIFY devicesChanged)
    Q_PROPERTY(QString ipv4 READ getIpv4 WRITE setIpv4 NOTIFY ipv4Changed)

    Q_INVOKABLE QString getNextHotspotName(QString p_name);

    void create() override;
    void saveAndActivate(const QString &p_devUni,const QString &p_apPath) override;
    QString getDevicePath(const QString &p_interfaceName) override;
    QStringList getDevices() override;

    QString getSsid();
    void setSsid(QString p_ssid);

    QString getPassword();
    void setPassword(QString p_password);

    QString getMode();
    void setMode(QString p_mode);

    bool getAutoconnect();
    void setAutoconnect(bool p_autoconnect);

    QString getIpv4();
    void setIpv4(QString p_ipv4);
signals:
    void ssidChanged();
    void passwordChanged();
    void modeChanged();
    void autoconnectChanged();
    void ipv4Changed();

private:
    QString m_smartConnectPath;
};

#endif // WIRELESSCONNECTIONSETTINGSINTERFACE_H
