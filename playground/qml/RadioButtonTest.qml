import QtQuick 2.9
import QtQuick.Controls 2.14
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.14
import ZeraComponents 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "ZRadioButton test"
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
                text: "Change vertical size or maximize"
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
            ButtonGroup { id: radioGroup }
            RowLayout {
                anchors.fill: parent
                RadioButton {
                    text: "RadioButton unchecked"
                    ButtonGroup.group: radioGroup
                }
                RadioButton {
                    checked: true
                    text: "ZRadioButton checked"
                    ButtonGroup.group: radioGroup
                }
            }
        }
        ButtonGroup { id: zradioGroup }
        Rectangle {
            color: Qt.darker("dimgrey", 3)
            width: parent.width
            height: lineHeight
            ZRadioButton {
                text: "ZRadioButton unchecked"
                anchors.fill: parent
                ButtonGroup.group: zradioGroup
            }
        }
        Rectangle {
            color: Qt.darker("dimgrey", 2)
            width: parent.width
            height: lineHeight
            ZRadioButton {
                checked: true
                text: "ZRadioButton checked"
                anchors.fill: parent
                ButtonGroup.group: zradioGroup
            }
        }
    }
}

