#ifndef QTWEBCHARTS_H
#define QTWEBCHARTS_H

class QwtCharts
{
public:
    static void registerQml();
private:
    static void registerTypes();
    static bool m_wasRegistered;
};

#endif // QTWEBCHARTS_H
