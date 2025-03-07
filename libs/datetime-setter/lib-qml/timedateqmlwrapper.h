#ifndef TIMEDATEQMLWRAPPER_H
#define TIMEDATEQMLWRAPPER_H

class TimedateQmlWrapper
{
public:
    static void registerQml();
private:
    static bool m_wasRegistered;
};

#endif // TIMEDATEQMLWRAPPER_H
