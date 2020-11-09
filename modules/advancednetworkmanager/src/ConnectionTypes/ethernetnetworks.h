#ifndef ETHERNETNETWORKS_H
#define ETHERNETNETWORKS_H

#include "abstractnetwork.h"

class EthernetNetworks :  public AbstractNetwork
{
public:
    EthernetNetworks();
    bool init(ConnectionList  &p_list, DeviceManager &p_devManager) override;
private:
    connectionItem CreateConItem(NetworkManager::Connection::Ptr p_con) override;
public slots:

};

#endif // ETHERNETNETWORKS_H
