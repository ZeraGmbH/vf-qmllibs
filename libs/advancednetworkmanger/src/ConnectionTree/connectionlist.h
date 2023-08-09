#ifndef CONNECTIONLIST_H
#define CONNECTIONLIST_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QSet>
#include <QVariant>

#include "globalDefines.h"

class ConnectionList;


/**
 * @brief The connectionItem class
 *
 * stores all data available in qml
 */
class connectionItem{
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

/**
 * @brief The ConnectionList class
 */

class ConnectionList : public QObject
{
    Q_OBJECT
public:
    ConnectionList();
    int addItem(connectionItem Item);
    bool removeItem(int p_index);
    bool removeByKey(int p_key);
    bool removeByPath(const QString &p_path);

    QList<connectionItem> items() const;
    QList<QString> paths() const;
    connectionItem itemByKey(int p_key);
    connectionItem itemByPath(QString p_path);
    bool setItemAt(int index, const connectionItem &p_item);
    bool setItemByKey(int p_key,const connectionItem &p_item);
    bool setItemByPath(QString p_key,const connectionItem &p_item);
private:
    int findKeyPos(int p_key);
    int findPathPos(const QString &Path);

    QList<connectionItem> m_list;
    uint m_uidCounter;

signals:
    void preItemRemoved(int i);
    void postItemRemoved(int i);

    void preItemAppended();
    void postItemAppended();

    void dataChanged(int p_row);

};

#endif // CONNECTIONLIST_H
