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

    Q_INVOKABLE QString getNextHotspotName(const QString &name);

    void create() override;
    void saveAndActivate(const QString &devUni,const QString &apPath) override;
    QString getDevicePath(const QString &interfaceName) override;
    QStringList getDevices() override;

    QString getSsid();
    void setSsid(const QString &ssid);

    QString getPassword();
    void setPassword(const QString &password);

    QString getMode();
    void setMode(const QString &mode);

    bool getAutoconnect();
    void setAutoconnect(bool autoconnect);

    QString getIpv4();
    void setIpv4(const QString &ipv4);
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
