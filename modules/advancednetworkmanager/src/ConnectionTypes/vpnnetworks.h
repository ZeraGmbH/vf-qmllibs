#ifndef VPNNETWORKS_H
#define VPNNETWORKS_H

#include "abstractnetwork.h"

class VpnNetworks : public AbstractNetwork
{
public:
    VpnNetworks();
    bool init(ConnectionList  &p_list, DeviceManager &p_devManager);
};

#endif // VPNNETWORKS_H
