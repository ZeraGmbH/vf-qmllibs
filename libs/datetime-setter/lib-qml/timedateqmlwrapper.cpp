#include "timedateqmlwrapper.h"
#include "timezonemodelsfacade.h"
#include <QtQml>

bool TimedateQmlWrapper::m_wasRegistered = false;

void TimedateQmlWrapper::registerQml()
{
    if (!m_wasRegistered) {
        qmlRegisterType<TimezoneModelsFacade>("Timedate", 1, 0, "TimedateModels");
        m_wasRegistered = true;
    }
}
