#include "zeracomponents.h"
#include "timedateqmlwrapper.h"

bool ZeraComponents::m_wasRegistered = false;

void ZeraComponents::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        TimedateQmlWrapper::registerQml();
        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}
