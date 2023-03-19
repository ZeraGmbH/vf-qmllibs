#include "zerafa.h"
#include <QtQml>

bool ZeraFa::m_wasRegistered = false;

void ZeraFa::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        qInfo("ZeraFa QML path: %s", qPrintable(debugQmlPath));
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}
