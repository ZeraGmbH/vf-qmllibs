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
    readonly property real editWidth: rowHeight * 1.6
    contentWidth: pointSize * 22
    contentHeight: (rowCount+1) * rowHeight
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    TimedateModels { id: timedateModels }
    onAboutToShow: {
        const currentDate = new Date()
        dayEdit.text = currentDate.getDate()
        monthEdit.text = currentDate.getMonth() + 1 // Javascript is zero based!!!
        yearEdit.text = currentDate.getFullYear()
        hourEdit.text = currentDate.getHours()
        minuteEdit.text = currentDate.getMinutes()
        secondEdit.text = currentDate.getSeconds()
    }

    ButtonGroup {
        id: radioGroup
    }
    ZRadioButton {
        id: ntpSync
        text: Z.tr("Network")
        anchors.top: parent.top
        height: rowHeight
        width: contentWidth
        ButtonGroup.group: radioGroup
    }
    ZRadioButton {
        id: internalRtc
        text: Z.tr("Internal clock")
        anchors.top: ntpSync.bottom
        height: rowHeight
        width: contentWidth
        ButtonGroup.group: radioGroup
    }
    Grid {
        id: grid
        columns: 6
        spacing: pointSize * 0.2
        anchors.top: internalRtc.bottom
        anchors.topMargin: rowHeight * 0.1
        anchors.left: parent.left
        anchors.leftMargin: pointSize * 4.75
        anchors.right: parent.right
        enabled: internalRtc.checked
        height: rowHeight * 3

        Label {
            text: Z.tr("Date:")
            height: rowHeight
            font.pointSize: pointSize
            verticalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: dayEdit
            width: editWidth
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            textAlignment: Text.AlignHCenter
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
            verticalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: monthEdit
            width: editWidth
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            textAlignment: Text.AlignHCenter
            validator: IntValidator {
                bottom: 1
                top: 12
            }
        }
        Label {
            text: "/"
            height: rowHeight
            font.pointSize: pointSize
            verticalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: yearEdit
            width: editWidth
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            textAlignment: Text.AlignHCenter
            validator: IntValidator {
                bottom: 2025
                top: 2500
            }
        }

        Label {
            text: Z.tr("Time:")
            height: rowHeight
            font.pointSize: pointSize
            verticalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: hourEdit
            width: editWidth
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            textAlignment: Text.AlignHCenter
            validator: IntValidator {
                bottom: 0
                top: 23
            }
        }
        Label {
            text: ":"
            height: rowHeight
            font.pointSize: pointSize
            verticalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: minuteEdit
            width: editWidth
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            textAlignment: Text.AlignHCenter
            validator: IntValidator {
                bottom: 0
                top: 59
            }
        }
        Label {
            text: ":"
            height: rowHeight
            font.pointSize: pointSize
            verticalAlignment: Label.AlignVCenter
        }
        ZLineEdit {
            id: secondEdit
            width: editWidth
            height: rowHeight
            pointSize: timeSetterPopup.pointSize
            textAlignment: Text.AlignHCenter
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
        anchors.bottomMargin: pointSize

        Item { Layout.fillWidth: true }
        readonly property real buttonWidth: Math.max(cancelButton.implicitWidth, okButton.implicitWidth) * 1.1
        Button {
            id: cancelButton
            text: Z.tr("Cancel")
            font.pointSize: pointSize
            Layout.preferredWidth: okCancelButtonRow.buttonWidth
            onClicked: {
                timeSetterPopup.close()
            }
        }
        Button {
            id: okButton
            text: Z.tr("OK")
            font.pointSize: pointSize
            Layout.preferredWidth: okCancelButtonRow.buttonWidth
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
