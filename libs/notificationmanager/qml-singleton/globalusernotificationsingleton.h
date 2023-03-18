#ifndef GLOBALUSERNOTIFICATIONSINGLETON_H
#define GLOBALUSERNOTIFICATIONSINGLETON_H

#include <QObject>

class GlobalUserNotificationSingleton : public QObject
{
    Q_OBJECT
public:
    static void registerQml();
private:
    static void registerTypes(const char* uri);
    static bool m_wasRegistered;
};

#endif // GLOBALUSERNOTIFICATIONSINGLETON_H
