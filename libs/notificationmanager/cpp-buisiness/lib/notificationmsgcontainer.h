#ifndef NOTIFICATIONMSGCONTAINER_H
#define NOTIFICATIONMSGCONTAINER_H

#include "notificationmsg.h"
#include <QObject>
#include <QVector>
#include <QMap>

class NotificationMsgContainer : public QObject
{
    Q_OBJECT
public:
    explicit NotificationMsgContainer();
    void addMsg(NotificationMsgPtr msg);
    void clear();
    QVector<NotificationMsgPtr> getMsgs();
signals:
    void sigMsgFaded();
private slots:
    void onMsgFaded(int id);
private:
    QMap<int, NotificationMsgPtr> m_msgs;
};

#endif // NOTIFICATIONMSGCONTAINER_H
