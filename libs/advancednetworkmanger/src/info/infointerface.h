#ifndef INFOINTERFACE_H
#define INFOINTERFACE_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QAbstractListModel>

#include <NetworkManagerQt/Manager>
#include <NetworkManagerQt/ActiveConnection>


class InfoStruct{
public:
    QString path;
    QString device;
    QString ipv4;
    QString subnetmask;
    QString ipv6;
};


class InfoInterface: public QAbstractListModel
{
     Q_OBJECT

public:
    InfoInterface();
    ~InfoInterface();

    enum InfoRoles {
        GroupeRole = Qt::UserRole + 1,
        ipv4Role,
        ipv6Role,
        subnetmaskRole,
        deviceRole,
    };


    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;


private:
    QList<InfoStruct> m_activeCons;

public slots:

    void addActiveConnection(const QString &p_path);
    void removeActiveConnection(const QString &p_path);
private slots:
    void ipv4Change();
    void ipv6Change();

signals:
    void aconsChanged();

};

#endif // INFOINTERFACE_H
