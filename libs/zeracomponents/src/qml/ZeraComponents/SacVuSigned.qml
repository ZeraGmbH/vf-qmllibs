import QtQuick 2.14
import QtQuick.Controls 2.14

SacVuDefaults {
    id: root
    property real undershootFactor: 0.1
    property color vuZeroIndicatorColor: Qt.lighter(vuBackColor, 5)

    readonly property int subVuCount: 2
    readonly property bool undershootActive: undershootFactor > 0 && undershootFactor < 1
    readonly property real undershootMagnifier: undershootActive ? subVuCount / (1+undershootFactor) : 1
    readonly property real relActual: actual / nominal
    readonly property bool focusPositive: !undershootActive ? relActual>=0 : relActual>=0
    Flickable {
        id: vu
        anchors.fill: parent
        clip: true
        interactive: false
        readonly property real widthMagnifier: !horizontal ? 1 : undershootMagnifier
        readonly property real heightMagnifier: horizontal ? 1 : undershootMagnifier
        contentWidth: width * widthMagnifier
        contentHeight: height * heightMagnifier
        contentX: !undershootActive ? 0 : 0
        contentY: !undershootActive ? 0 : 0
        SacVuBase {
            id: leftLowerVu
            x: 0
            width: parent.width / (horizontal ? subVuCount : 1)
            y: horizontal ? 0 : height
            height: parent.height / (horizontal ? 1 : subVuCount)

            nominal: root.nominal
            overshootFactor: root.overshootFactor
            actual: root.actual * (root.mirror ? 1 : -1)
            horizontal: root.horizontal
            mirror: true
            relIndicatorLen: root.relIndicatorLen
            relIndicatorWidth: root.relIndicatorWidth / undershootMagnifier
            vuBackColor: root.vuBackColor
            vuNominalColor: root.vuNominalColor
            vuOvershootColor1: root.vuOvershootColor1
            vuOvershootColor2: root.vuOvershootColor2
            vuOvershootIndicatorColor: root.vuOvershootIndicatorColor
            softOvershoot: root.softOvershoot
        }
        SacVuBase {
            id: rightUpperVu
            x: horizontal ? parent.width / subVuCount : 0
            width: parent.width / (horizontal ? subVuCount : 1)
            y: 0
            height: parent.height / (horizontal ? 1 : subVuCount)

            nominal: root.nominal
            overshootFactor: root.overshootFactor
            actual: root.actual * (root.mirror ? -1 : 1)
            horizontal: root.horizontal
            mirror: false
            relIndicatorLen: root.relIndicatorLen
            relIndicatorWidth: root.relIndicatorWidth / undershootMagnifier
            vuBackColor: root.vuBackColor
            vuNominalColor: root.vuNominalColor
            vuOvershootColor1: root.vuOvershootColor1
            vuOvershootColor2: root.vuOvershootColor2
            vuOvershootIndicatorColor: root.vuOvershootIndicatorColor
            softOvershoot: root.softOvershoot
        }
        SacVuIndicator {
            id: zeroIndicator
            color: vuZeroIndicatorColor

            horizontal: root.horizontal
            mirror: root.mirror
            relPosInVu: 0.5
            relIndicatorLen: root.relIndicatorLen
            relIndicatorWidth: root.relIndicatorWidth * 0.5 / undershootMagnifier
        }
    }
}
