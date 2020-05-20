#include "networkmanagerabstraction.h"
#include <NetworkManagerQt/Device>
#include <NetworkManagerQt/WirelessDevice>
#include <NetworkManagerQt/Settings>
#include <QString>
#include <QSet>

NetworkmanagerAbstraction::NetworkmanagerAbstraction(QObject* parent) : QObject(parent)
{

}

QStringList NetworkmanagerAbstraction::getAvailableSsids()
{
    QSet<QString> uniqueList;
    NetworkManager::Device::List list = NetworkManager::networkInterfaces();
    for(NetworkManager::Device::Ptr dev : list){
        if(dev->type() == NetworkManager::Device::Type::Wifi){
            NetworkManager::WirelessDevice::Ptr wdev = dev.staticCast<NetworkManager::WirelessDevice>();
            for(NetworkManager::WirelessNetwork::Ptr nw : wdev->networks()){
                uniqueList.insert(nw->ssid());
            }
        }
    }
    return uniqueList.toList();
}

void NetworkmanagerAbstraction::realoadConnections()
{
    NetworkManager::reloadConnections();
}
