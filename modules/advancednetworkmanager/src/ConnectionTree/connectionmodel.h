#ifndef CONMODELITEM_H
#define CONMODELITEM_H

#include <QAbstractListModel>
#include <QAbstractItemModel>
#include <QList>
#include <QMap>
#include <QHash>

class ConnectionList;

/**
 * @brief The ConnectionModel class
 */
class ConnectionModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ConnectionList *list READ getList NOTIFY listChanged)
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
        DeviceNames
    };

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                   int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    ConnectionList *getList() const;
    void setList(ConnectionList *list);

private:

    ConnectionList* m_list;
signals:
    void listChanged();

};

#endif // CONMODELITEM_H
