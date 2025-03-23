#include "timedateqmlwrapper.h"
#include "timedatehelper.h"
#include "timezonemodelsfacade.h"
#include "zeratranslationplugin.h"
#include <QtQml>

bool TimedateQmlWrapper::m_wasRegistered = false;

void TimedateQmlWrapper::registerQml()
{
    if (!m_wasRegistered) {
        ZeraTranslationPlugin::registerQml();
        qmlRegisterType<TimezoneModelsFacade>("Timedate", 1, 0, "TimedateModels");
        qmlRegisterType<TimeDateHelper>("Timedate", 1, 0, "TimedateHelper");
        m_wasRegistered = true;
    }
}
