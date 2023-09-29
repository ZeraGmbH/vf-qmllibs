import QtQuick 2.14
import QtQuick.Controls 2.14

Rectangle {
    id: vu
    // external interface
    property real nominal
    property real overshootFactor
    property real actual

    Rectangle { // top yellow -> red
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height * (1 - 1 / vu.overshootFactor)
        gradient: Gradient {
            GradientStop { position: 0; color: "red" }
            GradientStop { position: 0.5; color: "orange" }
            GradientStop { position: 1.0; color: "green" }
        }
    }
    Rectangle {
        color: "green"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height * 1 / vu.overshootFactor
    }
    Rectangle {
        id: topRect
        color: "grey"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height * (1 - vu.actual / (vu.overshootFactor * vu.nominal))
    }
}
