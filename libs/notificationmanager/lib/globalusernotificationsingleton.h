#ifndef GLOBALUSERNOTIFICATIONSINGLETON_H
#define GLOBALUSERNOTIFICATIONSINGLETON_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

class GlobalUserNotificationSingleton : public QObject
{
    Q_OBJECT
public:
    explicit GlobalUserNotificationSingleton(QObject *parent = nullptr);
    static QObject *getStaticInstance(QQmlEngine *t_engine, QJSEngine *t_scriptEngine);

signals:

};

#endif // GLOBALUSERNOTIFICATIONSINGLETON_H
