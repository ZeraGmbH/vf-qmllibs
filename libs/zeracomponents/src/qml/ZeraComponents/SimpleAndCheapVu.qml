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

    readonly property real overshootInvers: 1 / overshootFactor
    readonly property real overshootLen: 1 - overshootInvers

    Rectangle { // top/right yellow -> red
        x: horizontal ? parent.width * overshootInvers : 0
        width: parent.width * (horizontal ? overshootLen : 1)
        y: 0
        height: parent.height * (horizontal ? 1 : overshootLen)
        gradient: Gradient {
            orientation: horizontal ? Gradient.Horizontal : Gradient.Vertical
            GradientStop { position: horizontal ? 1 : 0; color: "red" }
            GradientStop { position: 0.5; color: "orange" }
            GradientStop { position: horizontal ? 0 : 1; color: "green" }
        }
    }
    Rectangle {
        color: "green"
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
}
