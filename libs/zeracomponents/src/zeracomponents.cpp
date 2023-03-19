#include "zeracomponents.h"
#include <QtQml>

bool ZeraComponents::m_wasRegistered = false;

void ZeraComponents::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        qInfo("ZeraComponents QML path: %s", qPrintable(debugQmlPath));
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}
