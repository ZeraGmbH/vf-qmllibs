import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import ZeraComponents 1.0

Item {
    id: unsignedView
    RowLayout {
        id: controlRow1
        anchors.top: parent.top
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        CheckBox {
            id: softOption
            text: "Soft"
        }
        CheckBox {
            id: mirrorOption
            text: "Mirror"
        }
    }
    Label {
        id: labelSliderRawVal
        anchors.top: controlRow1.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: Number(slider.value).toLocaleString(locale)
    }

    Slider {
        id: slider
        from: -0.1
        to: 1.1
        stepSize: 0.01
        wheelEnabled: true
        anchors.top: labelSliderRawVal.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.1
        height: 30
        orientation: Qt.Horizontal
    }

    readonly property real nominal: 100
    readonly property var overshootFactors: [1, 1.25, 1.5, 2, 3, 5, 10, 100]

    ListView {
        id: listView
        anchors.top: slider.bottom
        anchors.bottom: unsignedView.bottom
        width: parent.width
        orientation: ListView.Horizontal
        model: unsignedView.overshootFactors.length
        delegate: Rectangle {
            id: perVuRect
            height: listView.height
            width: listView.width / unsignedView.overshootFactors.length
            color: Material.backgroundColor
            border.color: Material.dividerColor
            border.width: 3
            readonly property real overshootVal: unsignedView.overshootFactors[index]
            readonly property real actualVal: slider.value * unsignedView.nominal * overshootVal
            Label {
                id: labelOvershootFactor
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                text: Number(perVuRect.overshootVal).toLocaleString(locale)
            }
            Label {
                id: labelActualValue
                anchors.top: labelOvershootFactor.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: Number(perVuRect.actualVal).toLocaleString(locale)
            }
            SacVuUnsigned {
                id: vuVertical
                softOvershoot: softOption.checked
                mirror: mirrorOption.checked
                anchors.top: labelActualValue.bottom
                anchors.bottom: vuHorizontal.top
                anchors.bottomMargin: parent.height * 0.05
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width * 0.1

                nominal: unsignedView.nominal
                overshootFactor: perVuRect.overshootVal
                actual: perVuRect.actualVal
            }
            SacVuUnsigned {
                id: vuHorizontal
                softOvershoot: softOption.checked
                mirror: mirrorOption.checked
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height * 0.05
                height: parent.height * 0.05
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width * 0.9

                nominal: unsignedView.nominal
                overshootFactor: perVuRect.overshootVal
                actual: perVuRect.actualVal
                horizontal: true
            }
        }
    }
}
