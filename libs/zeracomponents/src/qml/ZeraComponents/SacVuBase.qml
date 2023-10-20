import QtQuick 2.14
import QtQuick.Controls 2.14

SacVuDefaults {
    id: root
    readonly property real relOvershootPos: 1 / overshootFactor
    readonly property real actualLimitedToValid: {
        if(actual < 0)
            return 0
        let max = nominal * overshootFactor
        if(actual > max)
            return max
        return actual
    }
    function xor(a, b) {
        if(a !== b)
            return true
        return false
    }
    Rectangle {
        id: vu
        visible: true
        anchors.fill: parent
        readonly property real overshootColor1StartPos: softOvershoot ? 0.2 : 0
        Rectangle { // (soft: nominal color (green) ->) vuOvershootColor1 (yellow) -> vuOvershootColor2 (red)
            id: vuOvershootRect
            x: !mirror && horizontal ? parent.width * relOvershootPos : 0
            width: parent.width * (horizontal ? 1-relOvershootPos : 1)
            y: !mirror || horizontal ? 0 : parent.height - height
            height: parent.height * (horizontal ? 1 : 1-relOvershootPos)
            gradient: Gradient {
                orientation: horizontal ? Gradient.Horizontal : Gradient.Vertical
                GradientStop { position: xor(horizontal, mirror) ? 1 : 0; color: vuOvershootColor2 }
                GradientStop { position: xor(horizontal, mirror) ? vu.overshootColor1StartPos : 1-vu.overshootColor1StartPos; color: vuOvershootColor1 }
                // we hack green part out on non-soft by setting position to -1
                GradientStop { position: softOvershoot ? xor(horizontal, mirror) ? 0 : 1 : -1; color: vuNominalColor }
            }
        }
        Rectangle {
            id: vuNominalRect
            color: vuNominalColor
            x: !mirror || !horizontal ? 0 : parent.width * (1-relOvershootPos)
            y: !mirror || horizontal ? parent.height-height : 0
            width: parent.width * (horizontal ? relOvershootPos : 1)
            height: parent.height * (horizontal ? 1 : relOvershootPos)
        }
        Rectangle {
            id: hidingColorsRect
            color: vuBackColor
            x: horizontal && !mirror ? parent.width * (1-relativeLength) : 0
            y: !mirror || horizontal ? 0 : parent.height * (1-relativeLength)
            readonly property real relativeLength: (1 - actualLimitedToValid / (overshootFactor * nominal))

            width: horizontal ? parent.width * relativeLength : parent.width
            height: parent.height * (horizontal ? 1 : relativeLength)
        }
        SacVuIndicator {
            id: overshootStartIndicator
            color: vuOvershootIndicatorColor
            visible: overshootFactor > 1.0

            horizontal: root.horizontal
            mirror: root.mirror
            relPosInVu: root.relOvershootPos
            relIndicatorLen: root.relIndicatorLen
            relIndicatorWidth: root.relIndicatorWidth
        }
    }
}
