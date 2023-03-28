#include "zvkeyboardlayout.h"
#include <QByteArray>

void ZVKeyboardLayout::setKeyboardLayoutEnvironment()
{
    qputenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH", QByteArray(QML_SRC_PATH));
}
