#ifndef ZV_KEYBOARD_H
#define ZV_KEYBOARD_H

#include <zvkeyboard_export.h>
#include <QQmlApplicationEngine>

// our plugin wrapper for use by QML
class ZVKEYBOARD_EXPORT ZVKeyboard
{
public:
    /**
     * @brief setKeyboardLayoutEnvironment: Call this function in main() to enable customized keyboard layout
     */
    static void setKeyboardLayoutEnvironment();
    static void registerQml(QQmlApplicationEngine &engine);
private:
    static bool m_wasRegistered;
};

#endif // ZV_KEYBOARD_H


