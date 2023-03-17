#ifndef GLOBALUSERNOTIFICATIONSINGLETON_H
#define GLOBALUSERNOTIFICATIONSINGLETON_H

#include <QObject>

class GlobalUserNotificationSingleton : public QObject
{
    Q_OBJECT
public:
    explicit GlobalUserNotificationSingleton(QObject *parent = nullptr);

signals:

};

#endif // GLOBALUSERNOTIFICATIONSINGLETON_H
