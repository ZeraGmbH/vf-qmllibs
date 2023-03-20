#include "qwtcharts.h"
#include <QtQml>
#include "fftbarchart.h"
#include "hpwbarchart.h"
#include "barchart.h"
#include "cbar.h"

bool QwtCharts::m_wasRegistered = false;

void QwtCharts::registerQml()
{
    if(!m_wasRegistered) {
        registerTypes("QwtChart");
        m_wasRegistered = true;
    }
}

void QwtCharts::registerTypes(const char* uri)
{
    qmlRegisterType<FftBarChart>(uri, 1, 0, "FftBarChart");
    qmlRegisterType<HpwBarChart>(uri, 1, 0, "HpwBarChart");
    qmlRegisterType<BarChart>(uri, 1, 0, "BarChart");
    qmlRegisterType<cBar>(uri, 1, 0, "Bar");
}
