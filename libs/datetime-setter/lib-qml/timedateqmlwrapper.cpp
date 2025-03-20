#include "timedateqmlwrapper.h"
#include "timedatefacade.h"
#include "timezonemodelsfacade.h"
#include "zeratranslationplugin.h"
#include <QtQml>

bool TimedateQmlWrapper::m_wasRegistered = false;

void TimedateQmlWrapper::registerQml()
{
    if (!m_wasRegistered) {
        ZeraTranslationPlugin::registerQml();
        qmlRegisterType<TimezoneModelsFacade>("Timedate", 1, 0, "TimedateModels");
        qmlRegisterType<TimeDateFacade>("Timedate", 1, 0, "TimedateIO");
        m_wasRegistered = true;
    }
}
