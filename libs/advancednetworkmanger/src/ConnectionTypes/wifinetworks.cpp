#include "wifinetworks.h"
#include <NetworkManagerQt/WirelessDevice>
#include <NetworkManagerQt/WirelessSetting>

WifiNetworks::WifiNetworks()
{
    m_timer = nullptr;
}

WifiNetworks::~WifiNetworks()
{
    if(m_timer != nullptr){
        delete m_timer;
    }
}

bool WifiNetworks::init(ConnectionList  &p_list, DeviceManager &p_devManager)
{
    m_list=&p_list;
    m_devManager=&p_devManager;
    m_type= NetworkManager::Device::Type::Wifi;
    m_setType = NetworkManager::Setting::SettingType::Wireless;

    findStoredConnections();

    for(QString uni : m_devManager->getDevices(m_type)){
        findAvailableConnections(uni);
    }

    connect(m_devManager,&DeviceManager::addDevice,this,&AbstractNetwork::addDevice);
    connect(m_devManager,&DeviceManager::removeDevice,this,&AbstractNetwork::removeDevice);

    for(QString uni : m_devManager->getDevices(NetworkManager::Device::Type::Wifi)){
        DevStruct device;
        NetworkManager::Device::Ptr dev = m_devManager->getDevice(uni).dynamicCast<NetworkManager::WirelessDevice>();
        device.dev=dev;
        m_devList[uni]=device;
        device.qtCons.append(connect(device.dev.get(),&NetworkManager::WirelessDevice::stateChanged,this,[dev,this](NetworkManager::Device::State newstate, NetworkManager::Device::State oldstate, NetworkManager::Device::StateChangeReason reason){stateChanged(dev,newstate,oldstate,reason);
        }));

        device.qtCons.append(connect(device.dev.dynamicCast<NetworkManager::WirelessDevice>().data(),&NetworkManager::WirelessDevice::accessPointAppeared,this,[uni,this](const QString &p_apPath){
            addAccessPoint(uni,p_apPath);
        }));
        device.qtCons.append(connect(device.dev.dynamicCast<NetworkManager::WirelessDevice>().data(),&NetworkManager::WirelessDevice::accessPointDisappeared,this,[uni,this](const QString &p_apPath){
            removeAccessPoint(uni,p_apPath);
        }));
        device.qtCons.append(connect(device.dev.dynamicCast<NetworkManager::WirelessDevice>().data(),&NetworkManager::WirelessDevice::availableConnectionAppeared,this,[uni,this](const QString &p_apPath){
            addAvailabelConnection(uni,p_apPath);
        }));
        device.qtCons.append(connect(device.dev.dynamicCast<NetworkManager::WirelessDevice>().data(),&NetworkManager::WirelessDevice::availableConnectionDisappeared,this,[uni,this](const QString &p_apPath){
            removeAvailabelConnection(uni,p_apPath);
        }));
        findAPs(uni);
    }

    connect(NetworkManager::settingsNotifier(), &NetworkManager::SettingsNotifier::connectionAdded, this, &WifiNetworks::addConnection);
    connect(NetworkManager::settingsNotifier(), &NetworkManager::SettingsNotifier::connectionRemoved, this, &WifiNetworks::removeConnection);

    connect(NetworkManager::notifier(),&NetworkManager::Notifier::activeConnectionAdded,this,&WifiNetworks::connectionActivated);
    connect(NetworkManager::notifier(),&NetworkManager::Notifier::activeConnectionRemoved,this,&WifiNetworks::connectionDeactivate);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &WifiNetworks::onGetSignalStrength);
    m_timer->start(500);

    return true;
}

void WifiNetworks::findAPs(QString &p_uni)
{
    NetworkManager::WirelessDevice::Ptr dev;
    NetworkManager::AccessPoint::Ptr ap;

    NetworkManager::AccessPoint::Ptr apInList;
    NetworkManager::Connection::Ptr conInList;
    bool newData=true;

    dev = m_devManager->getDevice(p_uni).dynamicCast<NetworkManager::WirelessDevice>();
    DevStruct device;
    device.dev=dev;
    m_devList[p_uni]=device;
    for(QString path : dev->accessPoints()){
        newData = true;
        ap =  dev->findAccessPoint(path);
        ConStruct conBuf;
        conBuf.metaData.setValue(ConClassType::AP);
        conBuf.con.setValue(ap);
        if(m_conList.contains(path)){
            newData = false;
        }

        m_apList[path]=ap->ssid();

        for(ConStruct connection: m_conList.values()){
            if(connection.metaData.toInt() == (int)ConClassType::AP){
                if(connection.con.value<NetworkManager::AccessPoint::Ptr>()->ssid()== ap->ssid()){
                    newData=false;
                }
            }else{
                if(connection.con.value<NetworkManager::Connection::Ptr>()->settings()->setting(m_setType).dynamicCast<NetworkManager::WirelessSetting>()->ssid() == ap->ssid()){
                    newData=false;
                }
            }
        }

        if(ap->ssid() != ""){
            connectionItem con;
            con.Name=ap->ssid();
            con.Groupe="WIFI";
            con.NmPath=path;
            con.Available=true;
            con.Type=ConType::Wifi;
            con.Connected=false;
            con.Stored = false;
            con.SignalStrength=ap->signalStrength();
            con.Devices[m_devManager->getDevice(p_uni)->interfaceName()]=p_uni;
            if(newData){
                m_conList[path]=conBuf;
                m_list->addItem(con);
            }else{
                connectionItem con2=m_list->itemByPath(path);
                con2.SignalStrength=ap->signalStrength();
                con2.Available=true;
                for(QString key: con.Devices.keys()){
                    con2.Devices[key]=con.Devices[key];
                }
                m_list->setItemByPath(path,con2);
            }

        }
    }

}

connectionItem WifiNetworks::CreateConItem(const NetworkManager::Connection::Ptr p_con)
{
    NetworkManager::Setting::Ptr set = p_con->settings()->setting(m_setType);
    connectionItem con;
    con.Name=p_con->name();
    if(set.dynamicCast<NetworkManager::WirelessSetting>()->mode() == NetworkManager::WirelessSetting::NetworkMode::Ap){
        con.Groupe="HOTSPOT";
    }else{
        con.Groupe="WIFI";
    }
    con.NmPath=p_con->path();
    con.Available=false;
    con.Type=ConType::Wifi;
    con.Connected=isConnectionActive(p_con->path());
    con.Stored = true;
    con.SignalStrength=0;
    con.Ipv4 = getIpv4(p_con->path());
    return con;
}

void WifiNetworks::addAccessPoint(const QString &p_devUni, const QString &p_apPath)
{
    QString path = "";
    NetworkManager::WirelessDevice::Ptr device = m_devManager->getDevice(p_devUni).dynamicCast<NetworkManager::WirelessDevice>();
    NetworkManager::AccessPoint::Ptr ap = device->findAccessPoint(p_apPath);
    if(ap != nullptr) {
        ConStruct conBuf;
        conBuf.metaData.setValue(ConClassType::AP);
        conBuf.con.setValue(ap);
        bool newData = true;
        if(m_conList.contains(p_apPath))
            newData = false;
        m_apList[p_apPath]=ap->ssid();

        for(ConStruct connection: m_conList.values()) {
            if(connection.metaData.toInt() == (int)ConClassType::AP){
                if(connection.con.value<NetworkManager::AccessPoint::Ptr>()->ssid()== ap->ssid())
                    newData = false;
            }
            else if(connection.con.value<NetworkManager::Connection::Ptr>()->settings()->setting(m_setType).dynamicCast<NetworkManager::WirelessSetting>()->ssid() == ap->ssid())
                newData = false;
        }

        if(ap->ssid() != "") {
            connectionItem con;
            con.Name=ap->ssid();
            con.Groupe="WIFI";
            con.NmPath=p_apPath;
            con.Available=true;
            con.Type=ConType::Wifi;
            con.Connected=false;
            con.Stored = false;
            con.SignalStrength=ap->signalStrength();
            con.Devices[device->interfaceName()]=device->uni();
            if(newData) {
                m_conList[p_apPath]=conBuf;
                m_list->addItem(con);
            }
            else {
                connectionItem con2=m_list->itemByPath(p_apPath);
                con2 = m_list->itemByPath(path);
                con2.SignalStrength=ap->signalStrength();
                con2.Available=true;
                for(QString key: con.Devices.keys())
                    con2.Devices[key]=con.Devices[key];
                m_list->setItemByPath(path,con2);
            }
        }
    }
}

void WifiNetworks::removeAccessPoint(const QString &p_devUni, const QString &p_uni)
{
    bool managed=false;
    QString ssid = "";
    if(m_conList.contains(p_uni)){
        for(QMetaObject::Connection qtCon : m_conList[p_uni].qtCons){
            disconnect(qtCon);
        }
        ssid=m_list->itemByPath(p_uni).Name;
        m_conList.remove(p_uni);
        managed=true;
    }else if(m_apList.contains(p_uni)){
        ssid=m_apList[p_uni];
        m_apList.remove(p_uni);
        managed=true;
    }

    if(managed){
        m_list->removeByPath(p_uni);
        for(ConStruct connection: m_conList.values()){
            if(connection.metaData.toInt() != (int)ConClassType::AP){
                if(connection.con.value<NetworkManager::Connection::Ptr>()->settings()->setting(m_setType).dynamicCast<NetworkManager::WirelessSetting>()->ssid() == ssid){
                    connectionItem con2;
                    con2 = m_list->itemByPath(connection.con.value<NetworkManager::Connection::Ptr>()->path());
                    m_list->setItemByPath(connection.con.value<NetworkManager::Connection::Ptr>()->path(),con2);
                }
            }
        }
    }
}

void WifiNetworks::addConnection(const QString &connection)
{
    NetworkManager::Connection::Ptr conPtr = NetworkManager::findConnection(connection);
    QString conSsid="";
    if(connection != nullptr){
        NetworkManager::Setting::Ptr set = conPtr->settings()->setting(m_setType);
        if(set != NULL){
            conSsid=set.staticCast<NetworkManager::WirelessSetting>()->ssid();
            connectionItem conItm= CreateConItem(conPtr);
            for(QString ssid : m_apList){
                if(ssid == conSsid){
                    conItm.Available = true;
                }
            }
            addConnectionToList(conPtr,conItm);
        }
    }


    for(ConStruct conItem :  m_conList){
        if(conItem.metaData.toInt() == (int)ConClassType::AP){
            QString uni=conItem.con.value<NetworkManager::AccessPoint::Ptr>()->uni();
            QString apSsid = conItem.con.value<NetworkManager::AccessPoint::Ptr>()->ssid();
            if(apSsid == conSsid){
                m_conList.remove(uni);
                m_list->removeByPath(uni);
            }
            break;
        }
    }
}

void WifiNetworks::removeConnection(const QString &connection)
{
    AbstractNetwork::removeConnection(connection);
    for(QString uni : m_devManager->getDevices(m_type)){
        findAPs(uni);
    }
}

void WifiNetworks::addDevice(NetworkManager::Device::Type p_type, QString p_device){

    if(p_type == m_type){
        NetworkManager::Device::Ptr dev = m_devManager->getDevice(p_device).dynamicCast<NetworkManager::WirelessDevice>();
        DevStruct device;
        device.dev=dev;
        m_devList[p_device]=device;
        device.qtCons.append(connect(device.dev.dynamicCast<NetworkManager::WirelessDevice>().data(),&NetworkManager::WirelessDevice::accessPointAppeared,this,[p_device,this](const QString &p_apPath){
            addAccessPoint(p_device,p_apPath);
        }));
        device.qtCons.append(connect(device.dev.dynamicCast<NetworkManager::WirelessDevice>().data(),&NetworkManager::WirelessDevice::accessPointDisappeared,this,[p_device,this](const QString &p_apPath){
            removeAccessPoint(p_device,p_apPath);
        }));
        findAvailableConnections(p_device);
        device.qtCons.append(connect(device.dev.dynamicCast<NetworkManager::WirelessDevice>().data(),&NetworkManager::WirelessDevice::availableConnectionAppeared,this,[p_device,this](const QString &p_apPath){
            addAvailabelConnection(p_device,p_apPath);
        }));
        device.qtCons.append(connect(device.dev.dynamicCast<NetworkManager::WirelessDevice>().data(),&NetworkManager::WirelessDevice::availableConnectionDisappeared,this,[p_device,this](const QString &p_apPath){
            removeAvailabelConnection(p_device,p_apPath);
        }));
        findAPs(p_device);
    }
}

void WifiNetworks::onGetSignalStrength()
{
    for(QString uni : m_devManager->getDevices(NetworkManager::Device::Type::Wifi)) {
        NetworkManager::WirelessDevice::Ptr dev = m_devManager->getDevice(uni).dynamicCast<NetworkManager::WirelessDevice>();
        QStringList paths = dev->accessPoints();
        for(ConStruct connection : m_conList.values()) {
            QString ssid;
            QString path;
            if(connection.metaData.toInt() == (int)ConClassType::AP ) {
                NetworkManager::AccessPoint::Ptr apInList = connection.con.value<NetworkManager::AccessPoint::Ptr>();
                ssid = apInList->ssid();
                path = apInList->uni();
            }
            else {
                NetworkManager::Connection::Ptr conInList = connection.con.value<NetworkManager::Connection::Ptr>();
                ssid = conInList->settings()->setting(m_setType).dynamicCast<NetworkManager::WirelessSetting>()->ssid();
                path = conInList->path();
            }
            for(QString apPath : paths) {
                NetworkManager::AccessPoint::Ptr apDev = dev->findAccessPoint(apPath);
                if(ssid == apDev->ssid()){
                    connectionItem conItem;
                    conItem = m_list->itemByPath(path);
                    conItem.SignalStrength = apDev->signalStrength();
                    m_list->setItemByPath(path, conItem);
                }
            }
        }
    }
}

void WifiNetworks::stateChanged(NetworkManager::Device::Ptr dev, NetworkManager::Device::State newstate, NetworkManager::Device::State oldstate, NetworkManager::Device::StateChangeReason reason)
{
    if(oldstate==NetworkManager::Device::State::NeedAuth && newstate==NetworkManager::Device::State::Failed){
        QString device=dev->uni();

        NetworkManager::AccessPoint::Ptr acPoint = dev.dynamicCast<NetworkManager::WirelessDevice>()->activeAccessPoint();

        QString path;
        QString ssid;
        if(acPoint!=NULL){
            ssid=acPoint->ssid();
        }

        NetworkManager::ActiveConnection::Ptr actCon = dev->activeConnection();
        if(actCon != NULL){
            path=dev->activeConnection()->connection()->path();
            ssid=dev->activeConnection()->connection()->settings()->setting(m_setType).dynamicCast<NetworkManager::WirelessSetting>()->ssid();
            emit authFailed(ssid,path,device);
        }
    }
}
