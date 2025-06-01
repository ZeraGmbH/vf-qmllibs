#include "connectiontreeinterface.h"

ConnectionTreeInterface::ConnectionTreeInterface(QObject* parent) :
    QObject(parent),
    m_devManager(std::make_shared<DeviceManager>())
{
    std::shared_ptr<ConnectionList> list = std::make_shared<ConnectionList>();
    m_model.setConnectionList(list);

    QObject::connect(&m_wifiNets, &WifiNetworks::authFailed,
                     this, &ConnectionTreeInterface::authFailed);

    m_devManager->init();
    m_etherNets.init(list, m_devManager);
    m_wifiNets.init(list, m_devManager);
}

void ConnectionTreeInterface::removeConnection(QString p_path)
{
    NetworkManager::Connection::Ptr con = NetworkManager::findConnection(p_path);
    if(con != nullptr)
        con->remove();
}

QList<QString> ConnectionTreeInterface::getDevices(int p_type)
{
    if(p_type==(int)ConType::Wifi)
        return m_devManager->getDevices(NetworkManager::Device::Type::Wifi);
    else if(p_type==(int)ConType::Cable)
        return m_devManager->getDevices(NetworkManager::Device::Type::Ethernet);
    return m_devManager->getDevices(NetworkManager::Device::Type::UnknownType);
}

QString ConnectionTreeInterface::getDevice(QString p_conPath)
{
    QString ret;
    NetworkManager::Connection::Ptr con = NetworkManager::findConnection(p_conPath);
    if(con != nullptr){
        QString intName = con->settings()->interfaceName();
        NetworkManager::Device::List devList = m_devManager->getDevicesbyInterface(intName);
        if(devList.length() > 0)
            ret = devList.at(0)->uni();
    }
    return ret;
}

void ConnectionTreeInterface::connect(QString p_conPath, QString p_devPath, bool force)
{
    QString devPath = getDevice(p_conPath);
    if(devPath == "" || force)
        devPath = p_devPath;
    NetworkManager::activateConnection(p_conPath,p_devPath,"");
}

void ConnectionTreeInterface::disconnect(QString p_conPath)
{
    for(NetworkManager::ActiveConnection::Ptr acon : NetworkManager::activeConnections()) {
        if(acon->connection()->path() == p_conPath){
            NetworkManager::deactivateConnection(acon->path());
            break;
        }
    }
}

QAbstractListModel* ConnectionTreeInterface::getDataListQml()
{
    return &m_model;
}
