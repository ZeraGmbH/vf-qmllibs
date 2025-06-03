import QtQuick 2.9
import QtQuick.Controls 2.14
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.14
import ZeraComponents 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "ZCheckBox test"
    width: 800
    height: 400
    readonly property real lineHeight: height / 5
    Column {
        anchors.fill: parent
        Rectangle {
            color: Qt.darker("dimgrey", 3)
            width: parent.width
            height: lineHeight
            Label {
                text: "Change vertical size or maximize to see why ZCheckBox is cool"
                color: "lawngreen"
                font.pointSize: 20
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            color: Qt.darker("dimgrey", 2)
            width: parent.width
            height: lineHeight
            RowLayout {
                anchors.fill: parent
                CheckBox {
                    text: "CheckBox unchecked"
                }
                CheckBox {
                    checked: true
                    text: "CheckBox checked"
                }
                CheckBox {
                    tristate: true
                    checkState: Qt.PartiallyChecked
                    text: "CheckBox half-checked"
                }
            }
        }
        Rectangle {
            color: Qt.darker("dimgrey", 3)
            width: parent.width
            height: lineHeight
            ZCheckBox {
                text: "ZCheckBox unchecked"
                anchors.fill: parent
            }
        }
        Rectangle {
            color: Qt.darker("dimgrey", 2)
            width: parent.width
            height: lineHeight
            ZCheckBox {
                checked: true
                text: "ZCheckBox checked"
                anchors.fill: parent
            }
        }
        Rectangle {
            color: Qt.darker("dimgrey", 3)
            width: parent.width
            height: lineHeight
            ZCheckBox {
                tristate: true
                checkState: Qt.PartiallyChecked
                text: "ZCheckBox half-checked"
                anchors.fill: parent
            }
        }
    }
}

