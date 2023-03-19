#include "helpersplugin.h"
#include <QtQml>

bool HelpersPlugin::m_wasRegistered = false;

void HelpersPlugin::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        qInfo("HelpersPlugin QML path: %s", qPrintable(debugQmlPath));
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}
