#include "zeraveincomponents.h"
#include "zeracomponents.h"
#include <qmlfileio.h>

bool ZeraVeinComponents::m_wasRegistered = false;

void ZeraVeinComponents::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        QmlFileIO::registerQMLSingleton();
        ZeraComponents::registerQml(engine);

        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}
