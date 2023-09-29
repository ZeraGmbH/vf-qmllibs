import QtQuick 2.14
import QtQuick.Controls 2.14

Rectangle {
    id: vu
    // external interface
    property real nominal
    property real overshootFactor
    property real actual
    property bool horizontal: false


    Rectangle { // top yellow -> red
        x: horizontal ? parent.width * (1/vu.overshootFactor) : 0
        width: parent.width * (horizontal ? (1-1/vu.overshootFactor) : 1)
        y: 0
        height: parent.height * (horizontal ? 1 : (1-1/vu.overshootFactor))
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
        anchors.left: parent.left
        width: parent.width * (horizontal ? 1/vu.overshootFactor : 1)
        height: parent.height * (horizontal ? 1 : 1/vu.overshootFactor)
    }
    Rectangle {
        id: topRect
        color: "grey"
        x: horizontal ? parent.width * (1-relativeLenght) : 0
        y: 0
        readonly property real relativeLenght: (1 - vu.actual / (vu.overshootFactor * vu.nominal))
        width: horizontal ? parent.width * relativeLenght : parent.width
        height: parent.height * (horizontal ? 1 : relativeLenght)
    }
}
