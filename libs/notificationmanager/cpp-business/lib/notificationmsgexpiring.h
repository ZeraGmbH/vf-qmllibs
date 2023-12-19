#ifndef NOTIFICATIONMSGEXPIRING_H
#define NOTIFICATIONMSGEXPIRING_H

#include <timersingleshotqt.h>
#include "notificationmsg.h"

class NotificationMsgExpiring : public NotificationMsg
{
public:

    Q_PROPERTY(int timer WRITE setTimer NOTIFY onFaded)

    NotificationMsgExpiring();
    explicit NotificationMsgExpiring(QString msg, int fadeOutTimeMs);
    void setTimer(int fadeOutTimeMs);
private slots:
    void onFaded();
private:
    TimerTemplateQtPtr m_fadeOutTimer;
};

#endif // NOTIFICATIONMSGEXPIRING_H
