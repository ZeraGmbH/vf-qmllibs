#ifndef NOTIFICATIONMSG_H
#define NOTIFICATIONMSG_H

#include <QObject>

class NotificationMsg : public QObject
{
    Q_OBJECT
public:
    NotificationMsg(QString msg);
    QString getMsg();
signals:
    void sigFadeOut();
private:
    QString m_msg;
};

#endif // NOTIFICATIONMSG_H
