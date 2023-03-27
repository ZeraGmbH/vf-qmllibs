#include "zvkeyboardlayout.h"
#include <QByteArray>

void ZVKeyboardLayout::setKeyboardLayoutEnvironment()
{
    qputenv("import QtQuick.VirtualKeyboard 2.1QT_VIRTUALKEYBOARD_LAYOUT_PATH", QByteArray(QML_SRC_PATH));
}
