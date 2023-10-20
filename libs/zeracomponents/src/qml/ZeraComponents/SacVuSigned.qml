import QtQuick 2.14
import QtQuick.Controls 2.14

SacVuDefaults {
    id: root
    property color vuZeroIndicatorColor: Qt.lighter(vuBackColor, 10)
    property real vuZeroIndicatorShowRelRange: 0.3
    readonly property real relAbsActual: Math.abs(actual) / nominal
    property real vuZeroIndicatorOpacity: relAbsActual > vuZeroIndicatorShowRelRange ? 0 : 1-relAbsActual/vuZeroIndicatorShowRelRange
    Item {
        id: vu
        anchors.fill: parent
        SacVuBase {
            id: leftLowerVu
            x: 0
            width: parent.width / (horizontal ? 2 : 1)
            y: horizontal ? 0 : height
            height: parent.height / (horizontal ? 1 : 2)

            nominal: root.nominal
            overshootFactor: root.overshootFactor
            actual: root.actual * (root.mirror ? 1 : -1)
            horizontal: root.horizontal
            mirror: true
            relIndicatorLen: root.relIndicatorLen
            relIndicatorWidth: root.relIndicatorWidth
            vuBackColor: root.vuBackColor
            vuNominalColor: root.vuNominalColor
            vuOvershootColor1: root.vuOvershootColor1
            vuOvershootColor2: root.vuOvershootColor2
            vuOvershootIndicatorColor: root.vuOvershootIndicatorColor
            softOvershoot: root.softOvershoot
        }
        SacVuBase {
            id: rightUpperVu
            x: horizontal ? parent.width / 2 : 0
            width: parent.width / (horizontal ? 2 : 1)
            y: 0
            height: parent.height / (horizontal ? 1 : 2)

            nominal: root.nominal
            overshootFactor: root.overshootFactor
            actual: root.actual * (root.mirror ? -1 : 1)
            horizontal: root.horizontal
            mirror: false
            relIndicatorLen: root.relIndicatorLen
            relIndicatorWidth: root.relIndicatorWidth
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
            opacity: vuZeroIndicatorOpacity

            horizontal: root.horizontal
            mirror: root.mirror
            relPosInVu: 0.5
            relIndicatorLen: root.relIndicatorLen
            relIndicatorWidth: root.relIndicatorWidth * 0.5
        }
    }
}
