#ifndef ZERACOMPONENTS_H
#define ZERACOMPONENTS_H

#include <QQmlApplicationEngine>

class ZeraComponents
{
public:
    static void registerQml(QQmlApplicationEngine &engine);
private:
    static bool m_wasRegistered;
};

#endif // ZERACOMPONENTS_H
