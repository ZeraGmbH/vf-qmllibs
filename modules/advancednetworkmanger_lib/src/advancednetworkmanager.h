#ifndef ADVANCEDNETWORKMANAGER_H
#define ADVANCEDNETWORKMANAGER_H

#include <QObject>

class AdvancedNetworkmanager : public QObject
{
    Q_OBJECT
public:
    static void registerQml();
private:
    static void registerTypes(const char* uri);
    static bool m_wasRegistered;
};

#endif // ADVANCEDNETWORKMANAGER_H
