#ifndef ZERAFA_H
#define ZERAFA_H

#include <QQmlApplicationEngine>

class ZeraFa
{
public:
    static void registerQml(QQmlApplicationEngine &engine);
private:
    static bool m_wasRegistered;
};

#endif // ZERAFA_H
