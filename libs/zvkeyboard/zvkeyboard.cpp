#include "zvkeyboard.h"
#include <QByteArray>

void ZVKeyboard::setKeyboardLayoutEnvironment()
{
    qputenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH", QByteArray("qrc:/zvkeyboard/layouts"));
}

