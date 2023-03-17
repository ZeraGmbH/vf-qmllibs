#include "notificationmsg.h"

NotificationMsg::NotificationMsg(QString msg) :
    m_msg(msg)
{
}

QString NotificationMsg::getMsg()
{
    return m_msg;
}
