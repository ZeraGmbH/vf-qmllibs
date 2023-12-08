#ifndef WIREDCONNECTIONSETTINGSINTERFACE_H
#define WIREDCONNECTIONSETTINGSINTERFACE_H

#include "abstractconnectionsettingsinterface.h"

class WiredConnectionSettingsInterface : public AbstractConnectionSettingsInterface
{
    Q_OBJECT
public:
    Q_PROPERTY(QString ipv4Mode READ getIpv4Mode WRITE setIpv4Mode NOTIFY ipv4ModeChanged)
    Q_PROPERTY(QString ipv4 READ getIpv4 WRITE setIpv4 NOTIFY ipv4Changed)
    Q_PROPERTY(QString ipv4Sub READ getIpv4Sub WRITE setIpv4Sub NOTIFY ipv4SubChanged)
    Q_PROPERTY(QString ipv6Mode READ getIpv6Mode WRITE setIpv6Mode NOTIFY ipv6ModeChanged)
    Q_PROPERTY(QString ipv6 READ getIpv6 WRITE setIpv6 NOTIFY ipv6Changed)
    Q_PROPERTY(QString ipv6Sub READ getIpv6Sub WRITE setIpv6Sub NOTIFY ipv6SubChanged)

    void create() override;
    QStringList getDevices() override;

    QString getIpv4Mode();
    void setIpv4Mode(QString p_ipv4Mode);

    QString getIpv4();
    void setIpv4(QString p_ipv4);

    QString getIpv4Sub();
    void setIpv4Sub(QString p_ipv4Sub);

    QString getIpv6Mode();
    void setIpv6Mode(QString p_ipv6Mode);

    QString getIpv6();
    void setIpv6(QString p_ipv6);

    QString getIpv6Sub();
    void setIpv6Sub(QString p_ipv6Sub);

signals:
    void ipv4ModeChanged();
    void ipv4Changed();
    void ipv4SubChanged();
    void ipv6ModeChanged();
    void ipv6Changed();
    void ipv6SubChanged();
};

#endif // WIREDCONNECTIONSETTINGSINTERFACE_H
