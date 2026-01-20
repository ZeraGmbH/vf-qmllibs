#include "qwtcharts.h"
#include <QtQml>
#include "fftbarchart.h"
#include "hpwbarchart.h"
#include "cbar.h"

bool QwtCharts::m_wasRegistered = false;

void QwtCharts::registerQml()
{
    if(!m_wasRegistered) {
        registerTypes();
        m_wasRegistered = true;
    }
}

void QwtCharts::registerTypes()
{
    #define uri "QwtChart"
    qmlRegisterType<FftBarChart>(uri, 1, 0, "FftBarChart");
    qmlRegisterType<HpwBarChart>(uri, 1, 0, "HpwBarChart");
    qmlRegisterType<cBar>(uri, 1, 0, "Bar");
}
