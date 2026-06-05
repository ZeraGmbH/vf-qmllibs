#ifndef CONNECTIONTREEINTERFACE_H
#define CONNECTIONTREEINTERFACE_H

#include "connectionmodel.h"
#include "ethernetnetworks.h"
#include "wifinetworks.h"
#include <memory>

/**
 * @brief The ConnectionTreeInterface class
 *
 * This class connects the qml part with the C++ part.
 */
class ConnectionTreeInterface : public QObject
{
    Q_OBJECT
public:
    ConnectionTreeInterface(QObject* parent = nullptr);

    Q_PROPERTY(QAbstractListModel* dataList READ getDataListQml NOTIFY dummyNotify)

    Q_INVOKABLE void removeConnection(const QString &connectionPath);
    Q_INVOKABLE QList<QString> getDevices(int typeCableWifiOrUnknown);
    Q_INVOKABLE QString getDevice(const QString &connectionPath);
    Q_INVOKABLE void connect(const QString &connectionUniqueId, const QString &interfaceUniqueId);
    Q_INVOKABLE void disconnect(const QString &connectionPath);

    Q_INVOKABLE QString deduceSubNetMaskIpv4(const QString &ipAddress);
signals:
    void dummyNotify();
    void authFailed(const QString &name,const QString &path,const QString &device);

private:
    QAbstractListModel* getDataListQml();

    EthernetNetworks m_etherNets;
    WifiNetworks m_wifiNets;
    std::shared_ptr<DeviceManager> m_devManager;
    ConnectionModel m_model;
};

#endif // CONNECTIONTREEINTERFACE_H
