import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import ZeraLocale 1.0
import ZeraTranslation 1.0
import Timedate 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "TimedateSetter test"
    width: 800
    height: 800
    TimedateModels {
        id: timedateModels
    }

    RowLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        ComboBox {
            id: regions
            model: timedateModels.regionModel
            textRole: "regiontranslated"
            Layout.preferredWidth: 400
        }
        Item { Layout.fillWidth: true }
        ComboBox {
            id: langCombo
            Layout.preferredWidth: 200
            model: [ "en_GB", "en_US", "de_DE", "es_ES", "fr_FR", "pt_PT" ]
            function changeLanguage(newLocaleStr) {
                Z.changeLanguage(newLocaleStr);
                //VirtualKeyboardSettings.locale = newLocaleStr
                ZLocale.localeName = newLocaleStr
            }
            onCurrentTextChanged: {
                changeLanguage(langCombo.currentText)
            }
            Component.onCompleted: {
                changeLanguage(langCombo.currentText)
            }
        }
    }
}
