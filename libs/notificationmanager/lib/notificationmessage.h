#ifndef NOTIFICATIONMESSAGE_H
#define NOTIFICATIONMESSAGE_H

#include <QObject>

class NotificationMessage : public QObject
{
    Q_OBJECT
public:
    explicit NotificationMessage(QString msg, int fadeOutTimeMs);
    QString getMsg();
signals:
    void fadeOut();
};

#endif // NOTIFICATIONMESSAGE_H
