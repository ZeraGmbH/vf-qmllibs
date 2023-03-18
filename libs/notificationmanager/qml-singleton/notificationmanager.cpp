#include "notificationmanager.h"
#include <QtQml>

bool NotificationManager::m_wasRegistered = false;

void NotificationManager::registerQml()
{
    if(!m_wasRegistered) {
        m_wasRegistered = true;
        registerTypes("Notifications");
    }
}

void NotificationManager::registerTypes(const char *uri)
{
    Q_INIT_RESOURCE(notificationmanager);
    qmlRegisterType(QUrl("qrc:/qml/NotificationManager.qml"), uri, 1,0, "NotificationManager");
}
