import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14

Item {
    id: rootItm
    property int signals: 0
    Row {
        anchors.fill: parent
        spacing: parent.width/10
        Rectangle {
            width: parent.width/3-2
            height: parent.height/3
            anchors.bottom: parent.bottom
            border.color: Material.primaryTextColor
            color: rootItm.signals > 30 ? Material.primaryTextColor : Material.backgroundColor
        }
        Rectangle {
            width: parent.width/3-2
            height: parent.height/3*2
            anchors.bottom: parent.bottom
            border.color: Material.primaryTextColor
            color: rootItm.signals > 60 ? Material.primaryTextColor : Material.backgroundColor
        }
        Rectangle {
            width: parent.width/3-2
            height: parent.height
            anchors.bottom: parent.bottom
            border.color: Material.primaryTextColor
            color: rootItm.signals > 95 ? Material.primaryTextColor : Material.backgroundColor
        }
    }
}
