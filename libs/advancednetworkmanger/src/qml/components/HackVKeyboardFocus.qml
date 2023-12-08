import QtQuick 2.14
import QtQuick.VirtualKeyboard.Settings 2.2
import ZeraLocale 1.0

Item {
    // Explanation: At the time of writing QML shows odd behavior on focus
    // sequence:
    // enter ipv4: ipv4 activeFocus=true
    // enter sub4: sub4 activeFocus=true and THEN!! ipv4 activeFocus=true
    property int hackFieldFocusCount: 0
    function hackVKeyboardSettings(actFocus) {
        if(actFocus) {
            hackFieldFocusCount++
            VirtualKeyboardSettings.locale = "en_GB"
        }
        else {
            hackFieldFocusCount--
            if(hackFieldFocusCount === 0)
                VirtualKeyboardSettings.locale = ZLocale.localeName
        }
    }
}
