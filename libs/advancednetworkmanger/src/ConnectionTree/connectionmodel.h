#ifndef CONMODELITEM_H
#define CONMODELITEM_H

#include "connectionlist.h"
#include <QAbstractListModel>

class ConnectionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ConnectionModel(QObject *parent = nullptr);

    enum AnimalRoles {
        GroupeRole = Qt::UserRole + 1,
        NameRole,
        NmPathRole,
        AvailableRole,
        SignalStrengthRole,
        TypeRole,
        ConnectedRole,
        StoredRole,
        DeviceMap,
        DeviceNames,
        Ipv4
    };

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void setList(ConnectionList *list);

private:
    ConnectionList* m_list;
};

#endif // CONMODELITEM_H
