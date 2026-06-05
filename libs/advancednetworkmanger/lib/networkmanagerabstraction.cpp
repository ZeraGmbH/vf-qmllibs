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
    const NetworkManager::Device::List netwotkDeviceList = NetworkManager::networkInterfaces();
    for(const NetworkManager::Device::Ptr &dev : netwotkDeviceList) {
        if(dev->type() == NetworkManager::Device::Type::Wifi){
            NetworkManager::WirelessDevice::Ptr wdev = dev.staticCast<NetworkManager::WirelessDevice>();
            const NetworkManager::WirelessNetwork::List wirelessNetworkList = wdev->networks();
            for(const NetworkManager::WirelessNetwork::Ptr &nw : wirelessNetworkList)
                uniqueList.insert(nw->ssid());
        }
    }
    return uniqueList.values();
}
