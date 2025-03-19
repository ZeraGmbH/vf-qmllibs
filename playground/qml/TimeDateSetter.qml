import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import ZeraLocale 1.0
import ZeraTranslation 1.0
import ZeraComponents 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "TimedateSetter test"
    width: 800
    height: 800

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
    Label {
        id: currentTimeShort
        anchors.top: timezoneRow.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        text: Z.trDateTimeShort(Z.dateTimeNow)
    }
    Label {
        id: currentTimeShortTr
        anchors.top: currentTimeShort.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        text: {
            let now = Z.dateTimeNow
            return Z.trDateTimeShort(now) + " (" + Z.trDateTimeTz(now) + ")"
        }
    }
    Label {
        id: currentTimeLong
        anchors.top: currentTimeShortTr.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        text: Z.trDateTimeLong(Z.dateTimeNow)
    }
}
