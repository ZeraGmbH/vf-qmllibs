#include "infointerface.h"
#include "devicemanager.h"
#include <timersingleshotqt.h>

InfoInterface::InfoInterface()
{
    connect(NetworkManager::notifier(), &NetworkManager::Notifier::activeConnectionAdded,
            this, &InfoInterface::addActiveConnection);
    connect(NetworkManager::notifier(), &NetworkManager::Notifier::activeConnectionRemoved,
            this, &InfoInterface::removeActiveConnection);
    const NetworkManager::ActiveConnection::List activeConnections = NetworkManager::activeConnections();
    for(const NetworkManager::ActiveConnection::Ptr &activeConnection : activeConnections)
        addActiveConnection(activeConnection->path());
}

QHash<int, QByteArray> InfoInterface::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ipv4Role] = "ipv4";
    roles[ipv6Role] = "ipv6";
    roles[subnetmaskRole] = "subnetmask";
    roles[deviceRole] = "device";
    roles[typeRole] = "type";
    return roles;
}

int InfoInterface::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_activeCons.size();
}

QVariant InfoInterface::data(const QModelIndex &index, int role) const
{
    if(index.row() < m_activeCons.count()) {
        ConnectionInfoPtr entry = m_activeCons.at(index.row());
        switch(role){
        case ipv4Role:
            return entry->getIpV4();
        case subnetmaskRole:
            return entry->getSubnetMask();
        case ipv6Role:
            return entry->getIpV6();
        case deviceRole:
            return entry->getDevice();
        case typeRole:
            return entry->getType();
        }
    }
    return QVariant();
}

int InfoInterface::getEntryCount() const
{
    return rowCount();
}

void InfoInterface::addActiveConnection(const QString &path)
{
    NetworkManager::ActiveConnection::Ptr activeConnection = NetworkManager::findActiveConnection(path);
    if (activeConnection) {
        if (DeviceManager::isLocalHost(activeConnection))
            return;

        connect(activeConnection.data(), &NetworkManager::ActiveConnection::ipV4ConfigChanged, this, [=]() {
            startDetailsDelayTimer();
        });
        connect(activeConnection.data(), &NetworkManager::ActiveConnection::ipV6ConfigChanged, this, [=]() {
            startDetailsDelayTimer();
        });

        const int newIndex = m_activeCons.size();
        beginInsertRows(QModelIndex(), newIndex, newIndex);
        ConnectionInfoPtr newEntry = std::make_shared<ConnectionInfo>(activeConnection);
        m_activeCons.append(newEntry);
        endInsertRows();

        emit sigEntryCountChanged();
    }
}

int InfoInterface::findIdxByPath(const QString &path) const
{
    int idx = 0;
    for (const ConnectionInfoPtr &itm : qAsConst(m_activeCons)) {
        if(itm->getPath() == path)
            return idx;
        idx++;
    }
    return -1;
}

void InfoInterface::removeActiveConnection(const QString &path)
{
    int idx = findIdxByPath(path);
    if (idx < 0)
        return;
    beginRemoveRows(QModelIndex(), idx, idx);
    m_activeCons.removeAt(idx);
    endRemoveRows();
    emit sigEntryCountChanged();
}

void InfoInterface::startDetailsDelayTimer()
{
    m_delayTimer = std::make_unique<TimerSingleShotQt>(300);
    connect(m_delayTimer.get(), &TimerTemplateQt::sigExpired,
            this, &InfoInterface::updateActiveConnections);
    m_delayTimer->start();
}

void InfoInterface::updateActiveConnections()
{
    for (int idx=0; idx<m_activeCons.size(); idx++)
        if (m_activeCons[idx]->updateConnection())
            emit dataChanged(index(idx), index(idx));
}
