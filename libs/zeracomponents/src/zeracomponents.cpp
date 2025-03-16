#include "zeracomponents.h"
#include "timedateqmlwrapper.h"
#include <zerafa.h>

bool ZeraComponents::m_wasRegistered = false;

void ZeraComponents::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        TimedateQmlWrapper::registerQml();
        // Unfortunataley FontAwesomeQml does not work without further investigation...
        ZeraFa::registerQml(engine);

        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}
