#include "notificationmanager.h"
#include <QtQml>

bool NotificationManager::m_wasRegistered = false;

void NotificationManager::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}
