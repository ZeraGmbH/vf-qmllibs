#ifndef ZV_KEYBOARD_H
#define ZV_KEYBOARD_H

#include <QQmlApplicationEngine>

// our plugin wrapper for use by QML
class ZVKeyboardLayout
{
public:
    /**
     * @brief setKeyboardLayoutEnvironment: Call this function in main() to enable customized keyboard layout
     */
    static void setKeyboardLayoutEnvironment();
};

#endif // ZV_KEYBOARD_H


