#ifndef ADVANCEDNETWORKMANAGER_H
#define ADVANCEDNETWORKMANAGER_H

#include <QQmlApplicationEngine>

class AdvancedNetworkmanager
{
public:
    static void registerQml(QQmlApplicationEngine &engine);
private:
    static void registerCppTypes();
    static bool m_wasRegistered;
};

#endif // ADVANCEDNETWORKMANAGER_H
