#include "notificationmsgcontainer.h"

NotificationMsgContainer::NotificationMsgContainer()
{
}

void NotificationMsgContainer::addMsg(NotificationMsgPtr msg)
{
    m_msgs[msg->getId()] = msg;
    connect(msg.get(), &NotificationMsg::sigFadeOut,
            this, &NotificationMsgContainer::onMsgFaded);
}

void NotificationMsgContainer::clear()
{
    m_msgs.clear();
}

QVector<NotificationMsgPtr> NotificationMsgContainer::getMsgs()
{
    QVector<NotificationMsgPtr> returnedVector;
    for(auto &msg : m_msgs)
        returnedVector.append(msg);
    return returnedVector;
}

void NotificationMsgContainer::onMsgFaded(int id)
{
    if(m_msgs.contains(id))
        m_msgs.remove(id);
    emit sigMsgFaded();
}
