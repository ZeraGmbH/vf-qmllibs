#include "connectiontreeinterface.h"

ConnectionTreeInterface::ConnectionTreeInterface(QObject* parent) :
    QObject(parent),
    m_devManager(std::make_shared<DeviceManager>())
{
    QObject::connect(&m_wifiNets, &WifiNetworks::authFailed,
                     this, &ConnectionTreeInterface::authFailed);
    m_etherNets.init(m_model.getConnectionList(), m_devManager);
    m_wifiNets.init(m_model.getConnectionList(), m_devManager);
}

void ConnectionTreeInterface::removeConnection(const QString &connectionPath)
{
    NetworkManager::Connection::Ptr con = NetworkManager::findConnection(connectionPath);
    if(con != nullptr)
        con->remove();
}

QList<QString> ConnectionTreeInterface::getDevices(int typeCableWifiOrUnknown)
{
    if (typeCableWifiOrUnknown == (int)ConType::Wifi)
        return m_devManager->getDevices(NetworkManager::Device::Type::Wifi);
    if (typeCableWifiOrUnknown == (int)ConType::Cable)
        return m_devManager->getDevices(NetworkManager::Device::Type::Ethernet);
    return m_devManager->getDevices(NetworkManager::Device::Type::UnknownType);
}

QString ConnectionTreeInterface::getDevice(const QString &connectionPath)
{
    QString ret;
    NetworkManager::Connection::Ptr con = NetworkManager::findConnection(connectionPath);
    if(con != nullptr){
        QString intName = con->settings()->interfaceName();
        NetworkManager::Device::List devList = m_devManager->getDevicesbyInterface(intName);
        if(devList.length() > 0)
            ret = devList.at(0)->uni();
    }
    return ret;
}

void ConnectionTreeInterface::connect(const QString &connectionUniqueId, const QString &interfaceUniqueId)
{
    NetworkManager::activateConnection(connectionUniqueId, interfaceUniqueId, "");
}

void ConnectionTreeInterface::disconnect(const QString &connectionPath)
{
    for(NetworkManager::ActiveConnection::Ptr activeConnection : NetworkManager::activeConnections()) {
        if(activeConnection->connection()->path() == connectionPath) {
            NetworkManager::deactivateConnection(activeConnection->path());
            break;
        }
    }
}

QString ConnectionTreeInterface::deduceSubNetMaskIpv4(const QString &ipAddress)
{
    const QStringList ipEntries = ipAddress.split(".");
    if (ipEntries.size() != 4)
        return QString();

    if (ipEntries[0] == "192" && ipEntries[1] == "168") // Class C
        return "255.255.255.0";

    if (ipEntries[0] == "172") { // Class B
        int second = ipEntries[1].toInt();
        if (second >= 16 && second <= 31)
            return "255.255.0.0";
    }
    if (ipEntries[0] == "10") // Class A
        return "255.0.0.0";

    return QString();
}

QAbstractListModel* ConnectionTreeInterface::getDataListQml()
{
    return &m_model;
}
