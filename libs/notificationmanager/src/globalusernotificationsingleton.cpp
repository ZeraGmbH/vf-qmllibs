#include "globalusernotificationsingleton.h"

GlobalUserNotificationSingleton::GlobalUserNotificationSingleton(QObject *parent)
    : QObject{parent}
{

}

QObject *GlobalUserNotificationSingleton::getStaticInstance(QQmlEngine *t_engine, QJSEngine *t_scriptEngine)
{

}
