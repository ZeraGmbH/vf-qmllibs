#include "globalusernotificationsingleton.h"
#include <QtQml>

bool GlobalUserNotificationSingleton::m_wasRegistered = false;

void GlobalUserNotificationSingleton::registerQml()
{
    if(!m_wasRegistered) {
        m_wasRegistered = true;
        registerTypes("Notifications");
    }
}

void GlobalUserNotificationSingleton::registerTypes(const char *uri)
{
    Q_INIT_RESOURCE(notificationmanager);
    qmlRegisterType(QUrl("qrc:/qml/NotificationManager.qml"), uri, 1,0, "NotificationManager");
}
