import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14

SacVuDefaults {
    id: root
    readonly property real relOvershootPos: 1 / overshootFactor
    function xor(a, b) { return a !== b }
    Rectangle {
        id: vu
        visible: false
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
            readonly property real relativeLength: (1 - actual / (overshootFactor * nominal))

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
    /*Rectangle {
        id: fullBackForTest
        anchors.fill: parent
        color: "blue"
    }*/

    readonly property real vuStartDiameter: vuStartRadius*2
    readonly property real vuEndDiameter: vuEndRadius*2
    Item {
        id: radiusMask
        anchors.fill: parent
        visible: false
        Rectangle {
            id: startRadius
            radius: vuStartRadius
            x: horizontal ? (!mirror ? 0 : parent.width-vuStartDiameter) : 0
            width: !horizontal ? parent.width : vuStartDiameter
            y: !horizontal ? (mirror ? 0 : parent.height-vuStartDiameter) : 0
            height: horizontal ? parent.height : vuStartDiameter
        }
        Rectangle {
            id: middleRectNoRadius
            x: horizontal ? (!mirror ? vuStartRadius : vuEndRadius) : 0
            width: horizontal ? parent.width - (vuStartRadius + vuEndRadius) : parent.width
            y: !horizontal ? (mirror ? vuStartRadius : vuEndRadius) : 0
            height: !horizontal ? parent.height - (vuStartRadius + vuEndRadius) : parent.height
        }
        Rectangle {
            id: endRadius
            radius: vuEndRadius
            x: horizontal ? (mirror ? 0 : parent.width-vuEndDiameter) : 0
            width: !horizontal ? parent.width : vuEndDiameter
            y: !horizontal ? (!mirror ? 0 : parent.height-vuEndDiameter) : 0
            height: horizontal ? parent.height : vuEndDiameter
        }
    }
    OpacityMask {
        anchors.fill: parent
        source: vu
        maskSource: radiusMask
    }
}
