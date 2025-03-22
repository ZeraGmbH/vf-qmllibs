import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import ZeraTranslation 1.0
import ZeraTranslationBackend 1.0
import ZeraComponents 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "TimedateSetter test"
    width: 800
    height: 800

    ZvKeyboardInputPanel {
        id: inputPanel
        flickable: zvkFlickable
    }

    ZvKeyboardFlickable {
        id: zvkFlickable
        TimeSetterPopup {
            id: timesetterPopup
        }

        ComboBox {
            id: langCombo
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            model: [ "en_GB", "en_US", "de_DE", "es_ES", "fr_FR", "pt_PT" ]
            function changeLanguage(newLocaleStr) {
                Z.changeLanguage(newLocaleStr);
            }
            onCurrentTextChanged: {
                changeLanguage(langCombo.currentText)
            }
            Component.onCompleted: {
                changeLanguage(langCombo.currentText)
            }
        }
        TimezoneComboRow {
            id: timezoneRow
            anchors.top: langCombo.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }
        ColumnLayout {
            anchors.top: timezoneRow.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: parent.height * 0.03
            Label {
                id: currentTimeShort
                text: ZTR.trDateTimeShort(ZTR.dateTimeNow)
            }
            RowLayout {
                id: currentTimeShortTr
                Label {
                    text: {
                        let now = ZTR.dateTimeNow
                        return ZTR.trDateTimeShort(now) + " (" + ZTR.trDateTimeTz(now) + ")"
                    }
                    Layout.fillWidth: true
                }
                Button {
                    text: "..."
                    onClicked: timesetterPopup.open()
                }
            }
            Label {
                id: currentTimeLong
                text: ZTR.trDateTimeLong(ZTR.dateTimeNow)
            }
        }
    }
}
