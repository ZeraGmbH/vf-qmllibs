import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import ZeraLocale 1.0
import ZeraTranslation 1.0
import Timedate 1.0
import ZeraFa 1.0

Popup {
    id: timeSetterPopup
    property real pointSize: 15 // feel free to override

    anchors.centerIn: Overlay.overlay
    readonly property real rowHeight: pointSize * 2.5
    readonly property int rowCount: 5
    contentWidth: pointSize * 25
    contentHeight: (rowCount+1) * rowHeight
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    TimedateModels { id: timedateModels }
    ButtonGroup {
        id: radioGroup
    }
    ZRadioButton {
        id: ntpSync
        anchors.top: parent.top
        height: rowHeight
        text: Z.tr("Network")
        ButtonGroup.group: radioGroup
    }
    ZRadioButton {
        id: internalRtc
        anchors.top: ntpSync.bottom
        height: rowHeight
        text: Z.tr("Internal clock")
        ButtonGroup.group: radioGroup
    }
    Grid {
        id: grid
        columns: 6
        spacing: pointSize * 0.2
        anchors.top: internalRtc.bottom
        anchors.left: parent.left
        anchors.leftMargin: pointSize * 5
        anchors.right: parent.right
        enabled: internalRtc.checked

        height: rowHeight * 3
        Label {
            text: Z.tr("Date:")
            height: rowHeight
            font.pointSize: pointSize
            horizontalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: dayEdit
            width: rowHeight * 2
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            validator: IntValidator {
                bottom: 1
                top: {
                    let iYear = parseInt(yearEdit.text)
                    let iMonth = parseInt(monthEdit.text)
                    if(iYear > 0 && iMonth > 0)
                        return timedateModels.maxDaysInYearMonth(parseInt(yearEdit.text), parseInt(monthEdit.text))
                    return 31
                }
            }
        }
        Label {
            text: "/"
            height: rowHeight
            font.pointSize: pointSize
            horizontalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: monthEdit
            width: rowHeight * 2
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            validator: IntValidator {
                bottom: 1
                top: 12
            }
        }
        Label {
            text: "/"
            height: rowHeight
            font.pointSize: pointSize
            horizontalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: yearEdit
            width: rowHeight * 2
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            validator: IntValidator {
                bottom: 2025
                top: 2500
            }
        }

        Label {
            text: Z.tr("Time:")
            height: rowHeight
            font.pointSize: pointSize
            horizontalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: hourEdit
            width: rowHeight * 2
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            validator: IntValidator {
                bottom: 0
                top: 23
            }
        }
        Label {
            text: ":"
            height: rowHeight
            font.pointSize: pointSize
            horizontalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: minuteEdit
            width: rowHeight * 2
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            validator: IntValidator {
                bottom: 0
                top: 59
            }
        }
        Label {
            text: ":"
            height: rowHeight
            font.pointSize: pointSize
            horizontalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: secondEdit
            width: rowHeight * 2
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            validator: IntValidator {
                bottom: 0
                top: 59
            }
        }
    }
    RowLayout {
        id: okCancelButtonRow
        anchors.left: parent.left
        anchors.right: parent.right
        height: rowHeight
        anchors.bottom: parent.bottom
        anchors.bottomMargin: pointSize //* 0.5

        Item { Layout.fillWidth: true }
        Button {
            id: cancelButton
            text: Z.tr("Cancel")
            font.pointSize: pointSize
            Layout.preferredWidth: cancelButton.width
            onClicked: {
                timeSetterPopup.close()
            }
        }
        Button {
            id: okButton
            text: Z.tr("OK")
            font.pointSize: pointSize
            Layout.preferredWidth: cancelButton.width
            enabled: {
                if (ntpSync.checked)
                    return true
                return  internalRtc.checked &&
                        dayEdit.hasValidInput() &&
                        monthEdit.hasValidInput() &&
                        yearEdit.hasValidInput() &&
                        hourEdit.hasValidInput() &&
                        minuteEdit.hasValidInput() &&
                        secondEdit.hasValidInput()
            }
            onClicked: {

                timeSetterPopup.close()
            }
        }
    }
}
