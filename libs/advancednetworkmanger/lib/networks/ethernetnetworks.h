#ifndef ETHERNETNETWORKS_H
#define ETHERNETNETWORKS_H

#include "abstractnetwork.h"

class EthernetNetworks :  public AbstractNetwork
{
public:
    EthernetNetworks();
    bool init(std::shared_ptr<ConnectionList> connList, std::shared_ptr<DeviceManager> devManager) override;
private:
    ConnectionItem CreateConItem(NetworkManager::Connection::Ptr p_con) override;
};

#endif // ETHERNETNETWORKS_H
