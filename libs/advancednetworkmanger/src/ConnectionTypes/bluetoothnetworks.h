#ifndef BLUETOOTHNETWORKS_H
#define BLUETOOTHNETWORKS_H

#include "abstractnetwork.h"

class BluetoothNetworks : public AbstractNetwork
{
public:
    BluetoothNetworks();
    bool init(ConnectionList  &p_list, DeviceManager &p_devManager);
};

#endif // BLUETOOTHNETWORKS_H
