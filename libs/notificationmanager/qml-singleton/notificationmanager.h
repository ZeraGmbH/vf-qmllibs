#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

class NotificationManager
{
public:
    static void registerQml();
private:
    static void registerTypes(const char* uri);
    static bool m_wasRegistered;
};

#endif // NOTIFICATIONMANAGER_H
