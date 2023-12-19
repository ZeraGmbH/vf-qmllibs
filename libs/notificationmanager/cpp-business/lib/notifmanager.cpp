#include "notifmanager.h"
#include "notificationmsgcontainer.h"
#include <QtQml>

bool NotifManager::m_wasRegistered = false;

void NotifManager::registerQml()
{
    if(!m_wasRegistered) {
        registerType();
        m_wasRegistered = true;
    }
}

void NotifManager::registerType()
{
    qmlRegisterType<NotificationMsgContainer>("NotificationMsgContainer", 1, 0, "NotificationMsgContainer");
}
