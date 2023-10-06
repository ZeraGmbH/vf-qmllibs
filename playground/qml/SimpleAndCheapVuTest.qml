import QtQuick 2.14
import QtQuick.Controls 2.14
import Qt.labs.platform 1.0
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import ZeraComponents 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "Simple and cheap VU (that's the target :)"
    width: 800
    height: 400

    RowLayout {
        id: controlRow1
        anchors.top: parent.top
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        CheckBox {
            id: softOption
            text: "Soft"
        }
        /*CheckBox {
            text: "Header"
        }
        CheckBox {
            text: "Multi column"
        }*/
    }
    Label {
        id: labelSliderRawVal
        anchors.top: controlRow1.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: Number(slider.value).toLocaleString(locale)
    }

    Slider {
        id: slider
        anchors.top: labelSliderRawVal.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: mainWindow.width * 0.1
        height: 30
        orientation: Qt.Horizontal
    }


    readonly property real nominal: 100
    readonly property var overshootFactors: [1, 1.25, 1.5, 2, 3, 5, 10, 100]

    ListView {
        id: listView
        anchors.top: slider.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        orientation: ListView.Horizontal
        model: overshootFactors.length
        delegate: Rectangle {
            id: perVuRect
            height: listView.height
            width: listView.width / overshootFactors.length
            color: Material.backgroundColor
            border.color: Material.dividerColor
            border.width: 3
            readonly property real overshootVal: overshootFactors[index]
            Label {
                id: labelOvershootFactor
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                text: Number(perVuRect.overshootVal).toLocaleString(locale)
            }
            readonly property real actualVal: slider.value * nominal * overshootVal
            Label {
                id: labelActualValue
                anchors.top: labelOvershootFactor.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: Number(perVuRect.actualVal).toLocaleString(locale)
            }
            SimpleAndCheapVu {
                id: vuVertical
                softOvershoot: softOption.checked
                anchors.top: labelActualValue.bottom
                anchors.bottom: vuHorizontal.top
                anchors.bottomMargin: parent.height * 0.05
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width * 0.1

                nominal: mainWindow.nominal
                overshootFactor: perVuRect.overshootVal
                actual: perVuRect.actualVal
            }
            SimpleAndCheapVu {
                id: vuHorizontal
                softOvershoot: softOption.checked
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height * 0.05
                height: parent.height * 0.05
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width * 0.9

                nominal: mainWindow.nominal
                overshootFactor: perVuRect.overshootVal
                actual: perVuRect.actualVal
                horizontal: true
            }
        }
    }
}
