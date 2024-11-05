#ifndef CONNECTIONLIST_H
#define CONNECTIONLIST_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVariant>

class ConnectionList;

enum class ConType{Cable, Wifi};

class ConnectionItem
{
private:
    int uid;
public:
    QString Groupe;
    bool Stored;
    QString Name;
    QString NmPath;
    bool Available;
    int SignalStrength;
    ConType Type;
    bool Connected;
    QMap<QString,QVariant> Devices;
    QString Ipv4;
    friend class ConnectionList;
};

class ConnectionList : public QObject
{
    Q_OBJECT
public:
    ConnectionList();
    int addItem(ConnectionItem Item);
    bool removeByPath(const QString &p_path);

    QList<ConnectionItem> items() const;
    ConnectionItem itemByPath(QString p_path);
    bool setItemByPath(QString p_key,const ConnectionItem &p_item);
private:
    int findPathPos(const QString &Path);

    QList<ConnectionItem> m_connectionItemList;
    uint m_uidCounter;

signals:
    void preItemRemoved(int i);
    void postItemRemoved(int i);

    void preItemAppended();
    void postItemAppended();

    void dataChanged(int p_row);
};

#endif // CONNECTIONLIST_H
