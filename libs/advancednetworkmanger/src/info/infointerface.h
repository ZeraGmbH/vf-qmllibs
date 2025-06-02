#ifndef INFOINTERFACE_H
#define INFOINTERFACE_H

#include "connectioninfo.h"
#include <QAbstractListModel>
#include <QVariant>
#include <NetworkManagerQt/Manager>
#include <timertemplateqt.h>

class InfoInterface: public QAbstractListModel
{
     Q_OBJECT
public:
     enum InfoRoles {
         ipv4Role = Qt::UserRole + 1,
         ipv6Role,
         subnetmaskRole,
         deviceRole
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
