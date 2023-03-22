#ifndef ZERAVEINCOMPONENTS_H
#define ZERAVEINCOMPONENTS_H

#include <QQmlApplicationEngine>

class ZeraVeinComponents
{
public:
    static void registerQml(QQmlApplicationEngine &engine);
private:
    static bool m_wasRegistered;
};

#endif // ZERAVEINCOMPONENTS_H
