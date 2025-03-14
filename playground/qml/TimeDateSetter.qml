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

    ComboBox {
        id: langCombo
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        model: [ "en_GB", "en_US", "de_DE", "es_ES", "fr_FR", "pt_PT" ]
        function changeLanguage(newLocaleStr) {
            Z.changeLanguage(newLocaleStr);
            //ZLocale.localeName = newLocaleStr
        }
        onCurrentTextChanged: {
            changeLanguage(langCombo.currentText)
        }
        Component.onCompleted: {
            changeLanguage(langCombo.currentText)
        }
    }
    ColumnLayout {
        anchors.top: langCombo.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        RowLayout{
            ComboBox {
                id: regions
                Layout.preferredWidth: 390

                model: timedateModels.regionModel
                textRole: "regiontranslated"

                // Enlightment on how to do this with binding only is welcome
                readonly property int modelIndex: model.selectedIndex
                onCurrentIndexChanged: {
                    model.selectedIndex = currentIndex
                }
                onModelIndexChanged: {
                    currentIndex = modelIndex
                }

            }
            Item { Layout.fillWidth: true }
            ComboBox {
                id: cities
                Layout.preferredWidth: 390

                model: timedateModels.cityModel
                textRole: "cityorcountrytranslated"
            }
        }
    }
}
