import QtQuick 2.14
import QtQuick.Controls 2.14

Rectangle {
    id: vu
    // external interface
    property real nominal
    property real overshootFactor
    property real actual
    property bool horizontal: false
    property color vuBackColor: "dimgray"
    property color vuNominalColor: "lawngreen"
    property color vuOvershootColor1: "yellow"
    property color vuOvershootColor2: "red"
    property color vuOvershootIndicatorColor: vuNominalColor
    readonly property real overshoot1Start: 0.1

    readonly property real overshootInvers: 1 / overshootFactor
    readonly property real overshootLen: 1 - overshootInvers

    Rectangle { // top/right yellow -> red
        x: horizontal ? parent.width * overshootInvers : 0
        width: parent.width * (horizontal ? overshootLen : 1)
        y: 0
        height: parent.height * (horizontal ? 1 : overshootLen)
        gradient: Gradient {
            orientation: horizontal ? Gradient.Horizontal : Gradient.Vertical
            GradientStop { position: horizontal ? 1 : 0; color: vuOvershootColor2 }
            GradientStop { position: horizontal ? overshoot1Start : 1-overshoot1Start; color: vuOvershootColor1 }
            GradientStop { position: horizontal ? 0 : 1; color: vuNominalColor }
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
        id: topRect
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

        property real relNominalIndicatorLen: 0.8
        property real relNominalIndicatorWidth: 0.02

        property real indicatorWith: (horizontal ? parent.width : parent.height) * relNominalIndicatorWidth
        property real indicatorLen: (horizontal ? parent.height : parent.width) * relNominalIndicatorLen
        property real indicatorStart: ((horizontal ? parent.height : parent.width)-indicatorLen)/2
        radius: indicatorWith/2

        x: horizontal ? parent.width * overshootInvers-indicatorWith/2 : indicatorStart
        width: horizontal ? indicatorWith : indicatorLen
        y: horizontal ? indicatorStart : parent.height * overshootLen-indicatorWith/2
        height: horizontal ? indicatorLen : indicatorWith
    }
}
