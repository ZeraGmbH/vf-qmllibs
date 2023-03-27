#include "zvkeyboard.h"
#include <QByteArray>

bool ZVKeyboard::m_wasRegistered = false;

void ZVKeyboard::setKeyboardLayoutEnvironment()
{
    qputenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH", QByteArray("qrc:/zvkeyboard/layouts"));
}

void ZVKeyboard::registerQml(QQmlApplicationEngine &engine)
{
    if(!m_wasRegistered) {
        QString debugQmlPath = QStringLiteral(QML_SRC_PATH);
        engine.addImportPath(debugQmlPath);
        m_wasRegistered = true;
    }
}
