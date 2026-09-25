import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Switch {
    id: root
    indicator: Rectangle {
        id: bar
        implicitWidth: parent.width/19
        implicitHeight: parent.height/1.7
        x: root.leftPadding
        y: parent.height / 2 - height / 2
        radius: implicitHeight/2
        color: root.enabled ? (root.checked ? Material.switchCheckedTrackColor : Material.switchUncheckedTrackColor) : Material.switchDisabledTrackColor

        Rectangle {
            x: root.checked ? parent.width - width : 0
            width: parent.height*1.3
            height: width
            radius: width/2
            anchors.verticalCenter: bar.verticalCenter
            color: root.enabled ? (root.checked ? Material.switchCheckedHandleColor : Material.switchUncheckedHandleColor) : Material.switchDisabledHandleColor
            layer.enabled: true
            layer.effect: ElevationEffect {
                elevation: 6
            }
        }
    }
}
