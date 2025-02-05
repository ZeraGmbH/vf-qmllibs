#include "infointerface.h"
#include <NetworkManagerQt/Manager>

InfoInterface::InfoInterface()
{
    connect(NetworkManager::notifier(), &NetworkManager::Notifier::activeConnectionAdded,
            this, &InfoInterface::addActiveConnection);
    connect(NetworkManager::notifier(), &NetworkManager::Notifier::activeConnectionRemoved,
            this, &InfoInterface::removeActiveConnection);
    const NetworkManager::ActiveConnection::List activeConnections = NetworkManager::activeConnections();
    for(const NetworkManager::ActiveConnection::Ptr &acon : activeConnections)
        addActiveConnection(acon->path());
}

QHash<int, QByteArray> InfoInterface::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ipv4Role] = "ipv4";
    roles[ipv6Role] = "ipv6";
    roles[subnetmaskRole] = "subnetmask";
    roles[deviceRole] = "device";
    return roles;
}

int InfoInterface::rowCount(const QModelIndex &parent) const
{
    return m_activeCons.size();
}

QVariant InfoInterface::data(const QModelIndex &index, int role) const
{
    InfoStruct itm = m_activeCons.at(index.row());
    switch(role){
    case ipv4Role:
        return itm.ipv4;
        break;
    case subnetmaskRole:
        return itm.subnetmask;
        break;
    case ipv6Role:
        return itm.ipv6;
        break;
    case deviceRole:
        return itm.device;
        break;
    }
    return QVariant();
}

int InfoInterface::getEntryCount()
{
    return rowCount();
}

void InfoInterface::addActiveConnection(const QString &path)
{
    NetworkManager::ActiveConnection::Ptr acon = NetworkManager::findActiveConnection(path);
    if(acon) {
        // The connection data can change. They are also available later than the object.
        // So we connect the change event with this lambda function which updates the model.
        connect(acon.data(),&NetworkManager::ActiveConnection::ipV4ConfigChanged,this,&InfoInterface::ipv4Change);
        connect(acon.data(),&NetworkManager::ActiveConnection::ipV6ConfigChanged,this,&InfoInterface::ipv6Change);

        const int index = m_activeCons.size();
        beginInsertRows(QModelIndex(), index, index);
        InfoStruct itm;
        if(acon->ipV4Config().addresses().size()>0)
            itm.ipv4 = acon->ipV4Config().addresses().at(0).ip().toString();
        else
            itm.ipv4 = "N/A";
        if(acon->ipV4Config().addresses().size()>0)
            itm.subnetmask = acon->ipV4Config().addresses().at(0).netmask().toString();
        else
            itm.subnetmask = "N/A";
        if(acon->ipV6Config().addresses().size()>0)
            itm.ipv6= acon->ipV6Config().addresses().at(0).ip().toString();
        else
            itm.ipv6 = "N/A";
        if(acon->devices().size()>0)
            itm.device = NetworkManager::findNetworkInterface(acon->devices().at(0))->interfaceName();
        itm.path=path;
        m_activeCons.append(itm);
        endInsertRows();
    }
}

void InfoInterface::removeActiveConnection(const QString &path)
{
    int idx = 0;
    for(const InfoStruct &itm : qAsConst(m_activeCons)) {
        if(itm.path == path){
            beginRemoveRows(QModelIndex(), idx, idx);
            m_activeCons.removeAt(idx);
            endRemoveRows();
            break;
        }
        idx++;
    }
}

void InfoInterface::ipv4Change()
{
    // Searching for the corresponding model object using the path.
    for(int i = 0; i < this->m_activeCons.size(); ++i){
        NetworkManager::ActiveConnection::Ptr acon = NetworkManager::findActiveConnection(m_activeCons[i].path);
        if(!acon.isNull()){
            if(acon->ipV4Config().addresses().size()>0)
                m_activeCons[i].ipv4 = acon->ipV4Config().addresses().at(0).ip().toString();
            else
                m_activeCons[i].ipv4 = "N/A";
            if(acon->ipV4Config().addresses().size()>0)
                m_activeCons[i].subnetmask = acon->ipV4Config().addresses().at(0).netmask().toString();
            else
                m_activeCons[i].subnetmask = "N/A";
            emit this->dataChanged(this->index(i),this->index(i));
        }
    }
}

void InfoInterface::ipv6Change()
{
    for(int i = 0; i < this->m_activeCons.size(); ++i){
        NetworkManager::ActiveConnection::Ptr acon = NetworkManager::findActiveConnection(m_activeCons[i].path);
        if(!acon.isNull()){
            if(acon->ipV6Config().addresses().size()>0)
                m_activeCons[i].ipv6= acon->ipV6Config().addresses().at(0).ip().toString();
            else
                m_activeCons[i].ipv6 = "N/A";
            emit this->dataChanged(this->index(i),this->index(i));
        }
    }
}
