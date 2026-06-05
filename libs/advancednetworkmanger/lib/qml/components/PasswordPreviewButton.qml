import QtQuick 2.14
import QtQuick.Controls 2.5
import FontAwesomeQml 1.0
import ZeraComponents 1.0

ZButton {
    font.family: FAQ.fontFamily
    text: active ? FAQ.fa_eye : FAQ.fa_eye_slash
    // checkable: true looks ugly
    property bool active: false
    onPressed: active = !active
}
