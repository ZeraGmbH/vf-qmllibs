#ifndef NOTIFICATIONMSG_H
#define NOTIFICATIONMSG_H

#include <QObject>
#include <memory>

class NotificationMsg : public QObject
{
    Q_OBJECT
public:
    NotificationMsg(QString msg);
    QString getMsg();
    int getId();
signals:
    void sigFadeOut(int id);
protected:
    int m_id;
private:
    QString m_msg;
};

typedef std::shared_ptr<NotificationMsg> NotificationMsgPtr;

#endif // NOTIFICATIONMSG_H
