#include "abstractnetwork.h"
#include "nmcppnotification.h"
AbstractNetwork::AbstractNetwork()
{



}

void AbstractNetwork::connectionActivated(const QString &p_path)
{
    NetworkManager::ActiveConnection::Ptr acon = NetworkManager::findActiveConnection(p_path);
    if(acon!=nullptr){
    QString path = acon->connection()->path();
    if(m_conList.contains(path)){
        connectionItem itm = m_list->itemByPath(path);
        AconStruct acons;
        acons.path=path;
        acons.qtCons.append(connect(acon.get(),&NetworkManager::ActiveConnection::stateChangedReason,this,[path,this](NetworkManager::ActiveConnection::State state, NetworkManager::ActiveConnection::Reason reason){
            stateChangeReason(path,state,reason);
        }));
        m_aConList[p_path]=acons;
        if(itm.NmPath == path){
            itm.Available=true;
            m_list->setItemByPath(path,itm);
        }
    }
    }
}

void AbstractNetwork::connectionDeactivate(const QString &p_path)
{
    if(m_aConList.contains(p_path)){
        if(m_conList.contains(m_aConList[p_path].path)){
            QString path = m_aConList[p_path].path;
            for(QMetaObject::Connection qtcon : m_aConList[p_path].qtCons){
                disconnect(qtcon);
            }
            m_aConList.remove(p_path);
            connectionItem itm = m_list->itemByPath(path);
            itm.Connected=false;
            m_list->setItemByPath(path,itm);
        }

    }
}

void AbstractNetwork::addConnectionToList(NetworkManager::Connection::Ptr p_con, connectionItem conItem)
{
    QString path = p_con->path();
    if(!m_conList.contains(path)){
        ConStruct conBuf;
        conBuf.con.setValue(p_con);
        m_conList[path]=conBuf;
        m_conList[path].qtCons.append(connect(p_con.get(),&NetworkManager::Connection::updated,this,[path,this](){
            update(path);
        }));
        m_list->addItem(conItem);
    }else{

        connectionItem oldItem = m_list->itemByPath(path);

        for(QString key: oldItem.Devices.keys()){
            conItem.Devices[key]=oldItem.Devices[key];
        }


        if(oldItem.Available){
            conItem.Available=true;
        }
        if(oldItem.SignalStrength>conItem.SignalStrength){
            conItem.SignalStrength=oldItem.SignalStrength;
        }
        m_list->setItemByPath(path,conItem);
    }
}

void AbstractNetwork::findAvailableConnections(QString &p_uni)
{
    for(NetworkManager::Connection::Ptr connection : m_devManager->getDevice(p_uni)->availableConnections()){
        connectionItem conItm = CreateConItem(connection);
        conItm.Available=true;
        conItm.Devices[m_devManager->getDevice(p_uni)->interfaceName()]=p_uni;
        addConnectionToList(connection,conItm);
    }
}

void AbstractNetwork::findStoredConnections()
{
    bool newData=true;
    for(NetworkManager::Connection::Ptr connection : NetworkManager::listConnections()){
        newData=true;
        NetworkManager::Setting::Ptr set = connection->settings()->setting(m_setType);
        if(set != NULL){
            addConnectionToList(connection,CreateConItem(connection));
        }
    }
}

connectionItem AbstractNetwork::CreateConItem(NetworkManager::Connection::Ptr p_con)
{
    connectionItem item;
    return item;
}

bool AbstractNetwork::isConnectionActive(QString p_path)
{
    bool active = false;

    NetworkManager::ActiveConnection::List aConList = NetworkManager::activeConnections();
    for(NetworkManager::ActiveConnection::Ptr aCon : aConList){
        if(aCon->connection()->path() == p_path){
            m_aConList[aCon->path()].path=p_path;
            active = true;
            break;
        }
    }

    return active;

}

void AbstractNetwork::addConnection(const QString &p_path)
{
    NetworkManager::Connection::Ptr connection = NetworkManager::findConnection(p_path);
    if(connection != nullptr){
        NetworkManager::Setting::Ptr set = connection->settings()->setting(m_setType);
        if(set != NULL){
            addConnectionToList(connection,CreateConItem(connection));
        }
    }
}

void AbstractNetwork::removeConnection(const QString &p_uni)
{
    if(m_conList.contains(p_uni)){
        for(QMetaObject::Connection qtCon : m_conList[p_uni].qtCons){
            disconnect(qtCon);
        }
        m_conList.remove(p_uni);
        m_list->removeByPath(p_uni);
    }
}

void AbstractNetwork::addAvailabelConnection(const QString &p_devPath, const QString &p_connection)
{
    NetworkManager::Connection::Ptr connection = NetworkManager::findConnection(p_connection);
    connectionItem conItm = CreateConItem(connection);
    conItm.Devices[m_devManager->getDevice(p_devPath)->interfaceName()]=p_devPath;
    conItm.Available=true;
    addConnectionToList(connection,conItm);
}

void AbstractNetwork::removeAvailabelConnection(const QString &p_devPath, const QString &p_connection)
{
    connectionItem conItm;
    conItm=m_list->itemByPath(p_connection);
    if(conItm.Name != ""){
        for(QString key : conItm.Devices.keys()){
            if(conItm.Devices[key] == p_devPath){
                conItm.Devices.remove(key);
            }
            if(conItm.Devices.size() < 1){
                conItm.Available=false;
            }
            m_list->setItemByPath(p_connection,conItm);
        }
    }



}

void AbstractNetwork::addDevice(NetworkManager::Device::Type p_type, QString p_device)
{
    if(p_type == m_type){
        NetworkManager::Device::Ptr dev = m_devManager->getDevice(p_device);
        DevStruct device;
        device.dev=dev;
        m_devList[p_device]=device;
        findAvailableConnections(p_device);
        device.qtCons.append(connect(device.dev.data(),&NetworkManager::Device::availableConnectionDisappeared,this,[p_device,this](const QString &p_apPath){addAvailabelConnection(p_device,p_apPath);
        }));
        device.qtCons.append(connect(device.dev.data(),&NetworkManager::Device::availableConnectionDisappeared,this,[p_device,this](const QString &p_apPath){removeAvailabelConnection(p_device,p_apPath);
        }));
    }
}

void AbstractNetwork::removeDevice(QString p_device)
{
    if(m_devList.contains(p_device)){
        m_devList.remove(p_device);
        for(QMetaObject::Connection qtCon : m_devList[p_device].qtCons){
            disconnect(qtCon);
        }
    }
}

void AbstractNetwork::update(QString p_path)
{
    connectionItem con = m_list->itemByPath(p_path);
    if(con.Name != ""){
        if(m_conList.contains(p_path)){
            con.Name=m_conList[p_path].con.value<NetworkManager::Connection::Ptr>()->name();
            m_list->setItemByPath(p_path,con);
        }
    }
}

void AbstractNetwork::stateChangeReason(QString path, NetworkManager::ActiveConnection::State state, NetworkManager::ActiveConnection::Reason reason)
{
    NetworkManager::Connection::Ptr con =NetworkManager::findConnection(path);
    switch(reason){
    case NetworkManager::ActiveConnection::Reason::LoginFailed :
        NmCppNotification::sendNotifiaction("NM","Can not etablish connection. Wrong password!");
        break;
    case NetworkManager::ActiveConnection::Reason::DeviceDisconnected :
       // NmCppNotification::sendNotifiaction("NM","Can not etablish connection. Wrong password!");
        break;
    }

    connectionItem itm;
    if(m_conList.contains(path)){
         itm = m_list->itemByPath(path);
    }

    switch(state){
    case NetworkManager::ActiveConnection::State::Activated :
        if(itm.NmPath == path){
            itm.Connected=true;
            m_list->setItemByPath(path,itm);
        }
        NmCppNotification::sendNotifiaction("NM",QString("Connection ") + con->name() + QString(" etablished"));
        break;
    case NetworkManager::ActiveConnection::State::Deactivated:
        if(itm.NmPath == path){
            itm.Connected=false;
            m_list->setItemByPath(path,itm);
        }
        NmCppNotification::sendNotifiaction("NM",QString("Connection ") + con->name() + QString(" deactivated"));
        break;
    }
}


