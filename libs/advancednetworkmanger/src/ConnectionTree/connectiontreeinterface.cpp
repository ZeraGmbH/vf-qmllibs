#include "connectiontreeinterface.h"
#include "vpnnetworks.h"
#include "wifinetworks.h"
#include "ethernetnetworks.h"
#include "devicemanager.h"

#include <iostream>

ConnectionTreeInterface::ConnectionTreeInterface(QObject* parent) : QObject(parent)
{
    init();
}

void ConnectionTreeInterface::init()
{
    m_devManager=new DeviceManager();
    m_model = new ConnectionModel();
    ConnectionList* list =new ConnectionList();
    m_model->setList(list);
    m_networkTypeList.append(new EthernetNetworks());
    WifiNetworks *wtmpPtr=new WifiNetworks();
    m_networkTypeList.append(wtmpPtr);
    QObject::connect(wtmpPtr,&WifiNetworks::authFailed,this,&ConnectionTreeInterface::authFailed);
    m_devManager->init();

    for(auto it=m_networkTypeList.begin(); it != m_networkTypeList.end(); ++it){
        (*it)->init(*list,*m_devManager);
    }

}

void ConnectionTreeInterface::removeConnection(QString p_path)
{
    NetworkManager::Connection::Ptr con = NetworkManager::findConnection(p_path);
    if(con != NULL){
        con->remove();
    }
}

QList<QString> ConnectionTreeInterface::getDevices(int p_type)
{
    if(p_type==(int)ConType::Wifi){
        return m_devManager->getDevices(NetworkManager::Device::Type::Wifi);
    }else if(p_type==(int)ConType::Cable){
        return m_devManager->getDevices(NetworkManager::Device::Type::Ethernet);
    }
    return m_devManager->getDevices(NetworkManager::Device::Type::UnknownType);
}

QString ConnectionTreeInterface::getDevice(QString p_conPath)
{
    QString ret = "";
    NetworkManager::Device::List devList;
    QString intName;

    NetworkManager::Connection::Ptr con = NetworkManager::findConnection(p_conPath);
    if(con != nullptr){
        intName = con->settings()->interfaceName();
        devList = m_devManager->getDevicesbyInterface(intName);
        if(devList.length()>0){
            ret = devList.at(0)->uni();
        }
    }
    return ret;
}

void ConnectionTreeInterface::connect(QString p_conPath, QString p_devPath, bool force)
{
    QString devPath;
    devPath=getDevice(p_conPath);

    if(devPath == "" || force){
        devPath = p_devPath;
    }
    NetworkManager::activateConnection(p_conPath,p_devPath,"");
}



void ConnectionTreeInterface::disconnect(QString p_conPath)
{
    for(NetworkManager::ActiveConnection::Ptr acon : NetworkManager::activeConnections()){
        if(acon->connection()->path() == p_conPath){
            NetworkManager::deactivateConnection(acon->path());
            break;
        }
    }

}


QAbstractListModel* ConnectionTreeInterface::getDataListQml() const
{
    return m_model;
}

