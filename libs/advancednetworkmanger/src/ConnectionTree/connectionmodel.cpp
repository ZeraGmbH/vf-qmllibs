#include "connectionmodel.h"

ConnectionModel::ConnectionModel(QObject *parent) :
    QAbstractListModel(parent),
    m_connectionList(std::make_shared<ConnectionList>())
{
    connect(m_connectionList.get(), &ConnectionList::preItemAppended, this, [=]() {
        const int index = m_connectionList->items().size();
        beginInsertRows(QModelIndex(), index, index);
    });
    connect(m_connectionList.get(), &ConnectionList::postItemAppended, this, [=]() {
        endInsertRows();
    });

    connect(m_connectionList.get(), &ConnectionList::preItemRemoved, this, [=](int index) {
        beginRemoveRows(QModelIndex(), index, index);
    });
    connect(m_connectionList.get(), &ConnectionList::postItemRemoved, this, [=]() {
        endRemoveRows();
    });

    connect(m_connectionList.get(), &ConnectionList::dataChanged, this, [=](int p_row) {
        emit dataChanged(this->index(p_row),this->index(p_row));
    });
}

QHash<int, QByteArray> ConnectionModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[GroupeRole] = "groupe";
    roles[NameRole] = "name";
    roles[NmPathRole] = "nmPath";
    roles[AvailableRole] = "available";
    roles[SignalStrengthRole] = "signalStrength";
    roles[TypeRole] = "type";
    roles[ConnectedRole] = "connected";
    roles[StoredRole] = "stored";
    roles[DeviceMap] = "devices";
    roles[DeviceNames] = "deviceNames";
    roles[Ipv4] = "ipv4";
    return roles;
}

int ConnectionModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return m_connectionList->items().length();
}

QVariant ConnectionModel::data(const QModelIndex &index, int role) const
{

    ConnectionItem itm = m_connectionList->items().at(index.row());
    switch(role){
    case GroupeRole:
        return itm.Groupe;
        break;
    case NameRole:
        return itm.Name;
        break;
    case NmPathRole:
        return itm.NmPath;
        break;
    case AvailableRole:
        return itm.Available;
        break;
    case SignalStrengthRole:
        return itm.SignalStrength;
        break;
    case TypeRole:
        return (int) itm.Type;
        break;
    case ConnectedRole:
        return itm.Connected;
        break;
    case StoredRole:
        return itm.Stored;
        break;
    case DeviceMap:
        return itm.Devices;
    case DeviceNames:
        return QStringList(itm.Devices.keys());
        break;
    case Ipv4:
        return itm.Ipv4;
    default:
        return QVariant();
    }
}

bool ConnectionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    ConnectionItem itm = m_connectionList->items().at(index.row());
        switch(role){
        case GroupeRole:
            itm.Groupe = value.toString();
            break;
        case NameRole:
            itm.Name= value.toString();
            break;
        case NmPathRole:
            itm.NmPath= value.toString();
            break;
        case AvailableRole:
            itm.Available= value.toBool();
            break;
        case SignalStrengthRole:
            itm.SignalStrength= value.toInt();
            break;
        case TypeRole:
            itm.Type= (ConType)value.toInt();
            break;
        case ConnectedRole:
            itm.Connected= value.toBool();
            break;
        case StoredRole:
            itm.Stored= value.toBool();
            break;
        case DeviceMap:
          //  itm.Devices= value.toMap();
            break;
        case Ipv4:
            itm.Ipv4= value.toString();
            break;
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
}

Qt::ItemFlags ConnectionModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

std::shared_ptr<ConnectionList> ConnectionModel::getConnectionList()
{
    return m_connectionList;
}
