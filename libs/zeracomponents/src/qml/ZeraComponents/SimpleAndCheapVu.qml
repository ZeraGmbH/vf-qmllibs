import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14

Item {
    // external interface
    property real nominal
    property real overshootFactor
    property real actual
    property bool horizontal: false
    property bool mirror: false
    property color vuBackColor: "dimgray"
    property color vuNominalColor: "lawngreen"
    property color vuOvershootColor1: "yellow"
    property color vuOvershootColor2: "red"
    property color vuOvershootIndicatorColor: softOvershoot ? vuNominalColor : vuOvershootColor1
    property real vuEndRadius: horizontal ? height/2 : width/2
    property bool softOvershoot: false

    readonly property real overshootInvers: 1 / overshootFactor
    readonly property real overshootLen: 1 - overshootInvers
    readonly property real overshoot1Start: softOvershoot ? 0.2 : 0
    Rectangle {
        id: vu
        visible: false
        anchors.fill: parent
        Rectangle { // top/right yellow -> red
            x: horizontal ? parent.width * overshootInvers : 0
            width: parent.width * (horizontal ? overshootLen : 1)
            y: 0
            height: parent.height * (horizontal ? 1 : overshootLen)
            gradient: Gradient {
                orientation: horizontal ? Gradient.Horizontal : Gradient.Vertical
                GradientStop { position: horizontal ? 1 : 0; color: vuOvershootColor2 }
                GradientStop { position: horizontal ? overshoot1Start : 1-overshoot1Start; color: vuOvershootColor1 }
                // we hack green part out on non-soft by setting position to -1
                GradientStop { position: softOvershoot ? (horizontal ? 0 : 1) : -1; color: vuNominalColor }
            }
        }
        Rectangle {
            color: vuNominalColor
            anchors.bottom: parent.bottom
            x: 0
            width: parent.width * (horizontal ? overshootInvers : 1)
            height: parent.height * (horizontal ? 1 : overshootInvers)
        }
        Rectangle {
            id: hidingColorsRect
            color: vuBackColor
            x: horizontal ? parent.width * (1-relativeLength) : 0
            y: 0
            readonly property real relativeLength: (1 - actual / (overshootFactor * nominal))
            width: horizontal ? parent.width * relativeLength : parent.width
            height: parent.height * (horizontal ? 1 : relativeLength)
        }
        Rectangle {
            color: vuOvershootIndicatorColor
            visible: overshootFactor > 1.0

            property real relNominalIndicatorLen: 0.95
            property real relNominalIndicatorWidth: 0.02

            property real indicatorWith: (horizontal ? parent.width : parent.height) * relNominalIndicatorWidth
            property real indicatorLen: (horizontal ? parent.height : parent.width) * relNominalIndicatorLen
            property real indicatorStart: ((horizontal ? parent.height : parent.width)-indicatorLen)/2
            radius: indicatorWith/2

            readonly property real xFactor: !mirror ? overshootInvers : 1-overshootInvers
            x: horizontal ? parent.width*xFactor - indicatorWith/2 : indicatorStart
            width: horizontal ? indicatorWith : indicatorLen
            readonly property real yFactor: !mirror ? overshootLen : 1-overshootLen
            y:  horizontal ? indicatorStart : parent.height * yFactor - indicatorWith/2
            height: horizontal ? indicatorLen : indicatorWith
        }
    }
    Rectangle {
        id: radiusMask
        anchors.fill: parent
        radius: vuEndRadius
        visible: false
    }

    OpacityMask {
        anchors.fill: parent
        source: vu
        maskSource: radiusMask
    }

}

