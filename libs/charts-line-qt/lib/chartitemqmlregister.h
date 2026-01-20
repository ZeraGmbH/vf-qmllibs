#ifndef CHARTITEMQMLREGISTER_H
#define CHARTITEMQMLREGISTER_H

class ChartItemQmlRegister
{
public:
    static void registerQml();
private:
    static void registerTypes();
    static bool m_wasRegistered;
};

#endif // CHARTITEMQMLREGISTER_H
