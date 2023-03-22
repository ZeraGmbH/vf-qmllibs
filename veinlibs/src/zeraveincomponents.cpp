#include "zeraveincomponents.h"

bool ZeraVeinComponents::m_wasRegistered = false;

void ZeraVeinComponents::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}
