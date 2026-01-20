#include "chartitemqmlregister.h"
#include "chartitemqml.h"
#include <QQmlEngine>

bool ChartItemQmlRegister::m_wasRegistered = false;

void ChartItemQmlRegister::registerQml()
{
    if(!m_wasRegistered) {
        registerTypes();
        m_wasRegistered = true;
    }
}

void ChartItemQmlRegister::registerTypes()
{
    qmlRegisterType<ChartItemQml>("ChartItemQml", 1, 0, "ChartItemQml");
}
