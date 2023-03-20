#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QQmlApplicationEngine>

class NotificationManager
{
public:
    static void registerQml(QQmlApplicationEngine &engine);
private:
    static bool m_wasRegistered;
};

#endif // NOTIFICATIONMANAGER_H
