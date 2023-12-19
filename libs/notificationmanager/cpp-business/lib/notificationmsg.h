#ifndef NOTIFICATIONMSG_H
#define NOTIFICATIONMSG_H

#include <QObject>
#include <memory>

class NotificationMsg : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString msg READ getMsg WRITE setMsg)

    NotificationMsg();
    NotificationMsg(QString msg);
    QString getMsg() const;
    int getId() const;
    void setMsg(QString msg);

signals:
    void sigFadeOut(int id);

protected:
    const int m_id;
private:
    QString m_msg;
};

typedef std::shared_ptr<NotificationMsg> NotificationMsgPtr;

#endif // NOTIFICATIONMSG_H
