#include "ethernetnetworks.h"
#include <NetworkManagerQt/WiredDevice>

EthernetNetworks::EthernetNetworks()
{
}

bool EthernetNetworks::init(std::shared_ptr<ConnectionList> connList, std::shared_ptr<DeviceManager> devManager)
{
    m_list = connList;
    m_devManager = devManager;
    m_type = NetworkManager::Device::Type::Ethernet;
    m_setType = NetworkManager::Setting::SettingType::Wired;

    findStoredConnections();

    for(QString uni : m_devManager->getDevices(NetworkManager::Device::Type::Ethernet)){
        DevStruct device;
        device.dev=m_devManager->getDevice(uni).dynamicCast<NetworkManager::WiredDevice>();
        m_devList[uni]=device;

        device.qtCons.append(connect(device.dev.dynamicCast<NetworkManager::WiredDevice>().data(),&NetworkManager::WiredDevice::availableConnectionAppeared,this,[uni,this](const QString &p_apPath){
            addAvailabelConnection(uni,p_apPath);
        }));
        device.qtCons.append(connect(device.dev.dynamicCast<NetworkManager::WiredDevice>().data(),&NetworkManager::WiredDevice::availableConnectionDisappeared,this,[uni,this](const QString &p_apPath){
            removeAvailabelConnection(uni,p_apPath);
        }));

        findAvailableConnections(uni);
    }

    connect(m_devManager.get(), &DeviceManager::addDevice,
            this, &AbstractNetwork::addDevice);
    connect(m_devManager.get(), &DeviceManager::removeDevice,
            this, &AbstractNetwork::removeDevice);

    connect(NetworkManager::settingsNotifier(), &NetworkManager::SettingsNotifier::connectionAdded, this, &AbstractNetwork::addConnection);
    connect(NetworkManager::settingsNotifier(), &NetworkManager::SettingsNotifier::connectionRemoved, this, &AbstractNetwork::removeConnection);

    connect(NetworkManager::notifier(),&NetworkManager::Notifier::activeConnectionAdded,this,&EthernetNetworks::connectionActivated);
    connect(NetworkManager::notifier(),&NetworkManager::Notifier::activeConnectionRemoved,this,&EthernetNetworks::connectionDeactivate);

    return true;
}

ConnectionItem EthernetNetworks::CreateConItem(NetworkManager::Connection::Ptr p_con)
{
    ConnectionItem con;
    con.Name = p_con->name();
    con.Groupe = "ETHERNET";
    con.NmPath = p_con->path();
    con.Available = true;
    con.Stored = true;
    con.Type = ConType::Cable;
    con.Connected = isConnectionActive(p_con->path());
    con.SignalStrength = 100;
    con.Ipv4 = getIpv4(p_con->path());
    return con;
}
