#include "zeracomponents.h"
#include "timedateqmlwrapper.h"
#include <zerafa.h>

bool ZeraComponents::m_wasRegistered = false;

void ZeraComponents::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        // Add a dummy component so QML can import both Qt6 / Qt5 GraphicalEffects variants.
        // This has to go once we get rid of Qt5. Stolen from
        // https://stackoverflow.com/questions/69602129/use-qt5compat-graphicaleffects-in-qt6-and-qtgraphicaleffects-in-qt5-in-the-same
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        qmlRegisterModule("QtGraphicalEffects", 1, 14);
#else
        qmlRegisterModule("Qt5Compat.GraphicalEffects", 1, 0);
#endif
        TimedateQmlWrapper::registerQml();
        // Unfortunataley FontAwesomeQml does not work without further investigation...
        ZeraFa::registerQml(engine);

        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}
