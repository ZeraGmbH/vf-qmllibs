#ifndef HELPERSPLUGIN_H
#define HELPERSPLUGIN_H

#include <QQmlApplicationEngine>

class HelpersPlugin
{
public:
    static void registerQml(QQmlApplicationEngine &engine);
private:
    static bool m_wasRegistered;
};

#endif // HELPERSPLUGIN_H
