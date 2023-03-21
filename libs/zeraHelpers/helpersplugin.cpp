#include "helpersplugin.h"
#include <QtQml>

bool HelpersPlugin::m_wasRegistered = false;

void HelpersPlugin::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}
