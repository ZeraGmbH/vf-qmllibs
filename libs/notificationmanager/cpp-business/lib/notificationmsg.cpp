#include "notificationmsg.h"

static int currentId = 0;

NotificationMsg::NotificationMsg(const QString &msg) :
    m_id(currentId++),
    m_msg(msg)
{
}

const QString &NotificationMsg::getMsg() const
{
    return m_msg;
}

int NotificationMsg::getId() const
{
    return m_id;
}
