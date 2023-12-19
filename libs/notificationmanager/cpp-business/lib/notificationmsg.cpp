#include "notificationmsg.h"

static int currentId = 0;

NotificationMsg::NotificationMsg() :
    m_id(currentId++)
{
}

NotificationMsg::NotificationMsg(QString msg) :
    m_id(currentId++),
    m_msg(msg)
{
}

QString NotificationMsg::getMsg() const
{
    return m_msg;
}

int NotificationMsg::getId() const
{
    return m_id;
}

void NotificationMsg::setMsg(QString msg)
{
    m_msg = msg;
}
