import QtQuick 2.14
import QtQuick.Controls 2.14

Flickable {
    property alias animation: flickAnimation
    anchors.fill: parent
    enabled: true
    contentWidth: parent.width;
    contentHeight: parent.height
    boundsBehavior: Flickable.StopAtBounds
    interactive: false
    NumberAnimation on contentY {
        duration: 300
        id: flickAnimation
    }
}
