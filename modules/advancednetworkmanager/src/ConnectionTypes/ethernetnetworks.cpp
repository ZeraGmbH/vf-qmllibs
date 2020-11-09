#include "ethernetnetworks.h"


EthernetNetworks::EthernetNetworks()
{
}

bool EthernetNetworks::init(ConnectionList  &p_list, DeviceManager &p_devManager)
{
    m_list = &p_list;
    m_devManager = &p_devManager;
    m_type = NetworkManager::Device::Type::Ethernet;
    m_setType = NetworkManager::Setting::SettingType::Wired;

    findStoredConnections();

    for(QString uni : m_devManager->getDevices(NetworkManager::Device::Type::Ethernet)){
        findAvailableConnections(uni);
    }

    connect(NetworkManager::settingsNotifier(), &NetworkManager::SettingsNotifier::connectionAdded, this, &AbstractNetwork::addConnection);
    connect(NetworkManager::settingsNotifier(), &NetworkManager::SettingsNotifier::connectionRemoved, this, &AbstractNetwork::removeConnection);

    connect(NetworkManager::notifier(),&NetworkManager::Notifier::activeConnectionAdded,this,&EthernetNetworks::connectionActivated);
    connect(NetworkManager::notifier(),&NetworkManager::Notifier::activeConnectionRemoved,this,&EthernetNetworks::connectionDeactivate);

    return true;
}

connectionItem EthernetNetworks::CreateConItem(NetworkManager::Connection::Ptr p_con)
{
    connectionItem con;
    con.Name = p_con->name();
    con.Groupe = "ETHERNET";
    con.NmPath = p_con->path();
    con.Available = true;
    con.Stored = true;
    con.Type = ConType::Cable;
    con.Connected = isConnectionActive(p_con->path());
    con.SignalStrength = 100;
    return con;
}







