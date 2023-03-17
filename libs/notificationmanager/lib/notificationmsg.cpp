#include "notificationmsg.h"

static int currentId = 0;

NotificationMsg::NotificationMsg(QString msg) :
    m_msg(msg),
    m_id(currentId++)
{
}

QString NotificationMsg::getMsg()
{
    return m_msg;
}

int NotificationMsg::getId()
{
    return m_id;
}
