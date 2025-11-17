#ifndef INFOINTERFACE_H
#define INFOINTERFACE_H

#include "connectioninfo.h"
#include <timertemplateqt.h>
#include <NetworkManagerQt/Manager>
#include <QAbstractListModel>
#include <QVariant>

class InfoInterface: public QAbstractListModel
{
    Q_OBJECT
public:
    enum InfoRoles {
        ipv4Role = Qt::UserRole + 1,
        ipv6Role,
        subnetmaskRole,
        deviceRole,
        typeRole // int - see NetworkManager::Device::Type in networkmanager-qt5/device.h
    };

    InfoInterface();
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_PROPERTY(int entryCount READ getEntryCount NOTIFY sigEntryCountChanged)
    int getEntryCount() const;
signals:
    void sigEntryCountChanged();

private slots:
    void addActiveConnection(const QString &path);
    void removeActiveConnection(const QString &path);
    void updateActiveConnections();
private:
    void startDetailsDelayTimer();
    int findIdxByPath(const QString &path) const;

    QList<ConnectionInfoPtr> m_activeCons;
    TimerTemplateQtPtr m_delayTimer;
};

#endif // INFOINTERFACE_H
