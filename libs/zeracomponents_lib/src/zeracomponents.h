#ifndef ZERACOMPONENTS_H
#define ZERACOMPONENTS_H

#include <QObject>

class ZeraComponents : public QObject
{
    Q_OBJECT
public:
    static void registerQml();
private:
    static void registerTypes(const char* uri);
    static bool m_wasRegistered;
};

#endif // ZERACOMPONENTS_H
