#ifndef CONNECTIONLIST_H
#define CONNECTIONLIST_H

#include "connectionitem.h"
#include <QString>

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
