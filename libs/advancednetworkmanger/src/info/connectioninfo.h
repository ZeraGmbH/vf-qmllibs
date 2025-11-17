#ifndef CONNECTIONINFO_H
#define CONNECTIONINFO_H

#include <NetworkManagerQt/ActiveConnection>
#include <memory>

class ConnectionInfo {
public:
    explicit ConnectionInfo(NetworkManager::ActiveConnection::Ptr activeConnection);
    QString getPath() const;
    QString getDevice() const;
    QString getType() const;
    bool updateConnection();

    const QString getIpV4() const;
    const QString getSubnetMask() const;
    const QString getIpV6() const;
private:
    const QString getNaAdjustedValue(const QString &value) const;
    bool setDevice(const QString &device);
    bool setType(const QString &typeStr);
    bool setIpV4(const QString &ipv4);
    bool setSubnetMask(const QString &subnetmask);
    bool setIpV6(const QString &ipv6);

    NetworkManager::ActiveConnection::Ptr m_activeConnection;
    QString m_ipv4;
    QString m_subnetmask;
    QString m_ipv6;
    QString m_device;
    QString m_type;
};

typedef std::shared_ptr<ConnectionInfo> ConnectionInfoPtr;

#endif // CONNECTIONINFO_H
