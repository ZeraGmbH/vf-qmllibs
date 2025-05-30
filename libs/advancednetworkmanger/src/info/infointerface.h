#ifndef INFOINTERFACE_H
#define INFOINTERFACE_H

#include <QAbstractListModel>
#include <QHash>
#include <QVariant>
#include <NetworkManagerQt/Manager>

class InfoInterface: public QAbstractListModel
{
     Q_OBJECT
public:
     enum InfoRoles {
         GroupeRole = Qt::UserRole + 1,
         ipv4Role,
         ipv6Role,
         subnetmaskRole,
         deviceRole,
     };

    InfoInterface();
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_PROPERTY(int entryCount READ getEntryCount NOTIFY sigEntryCountChanged)
    int getEntryCount();
signals:
    void sigEntryCountChanged();

private:
    struct InfoStruct
    {
        QString path;
        QString device;
        QString ipv4;
        QString subnetmask;
        QString ipv6;
    };
    QList<InfoStruct> m_activeCons;
private slots:
    void addActiveConnection(const QString &path);
    void removeActiveConnection(const QString &path);
    void ipv4Change();
    void ipv6Change();
private:
    void modifyV4(InfoStruct &connection, const NetworkManager::IpAddresses &v4Adresses);
    void modifyV6(InfoStruct &connection, const NetworkManager::IpAddresses &v6Adresses);
};

#endif // INFOINTERFACE_H
