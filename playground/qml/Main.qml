import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.12

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "playground"

    width: 400
    height: 600

    Loader {
        id: commonLoader
        anchors.left: mainWindow.right
        anchors.top: mainWindow.top
    }

    GridLayout {
        anchors.fill: parent
        columns: 2
        CheckBox {
            id: showanmsettings
            checked: false;
            Layout.fillWidth: true;
            text: "Load anmsettings"
            onCheckStateChanged: {
                if(checked){
                    commonLoader.active=true;
                    commonLoader.source = "Anmsettings.qml";
                }else{
                    commonLoader.active=false;
                }
            }
        }
        CheckBox {
            id: shownotifmanager
            checked: false;
            Layout.fillWidth: true;
            text: "Load notifiManager"
            onCheckStateChanged: {
                if(checked){
                    commonLoader.active=true;
                    commonLoader.source = "NotifiManager.qml";
                }else{
                    commonLoader.active=false;
                }
            }
        }
        CheckBox {
            Layout.fillWidth: true;
            text: "Load VU"
            onCheckStateChanged: {
                if(checked) {
                    commonLoader.active=true;
                    commonLoader.source = "SacVuTest.qml";
                }
                else
                    commonLoader.active=false;
            }
        }
        CheckBox {
            checked: false;
            Layout.fillWidth: true;
            text: "Load ZComboBox"
            onCheckStateChanged: {
                if(checked){
                    commonLoader.active=true;
                    commonLoader.source = "ComboBoxTest.qml";
                }
                else
                    commonLoader.active=false;
            }
        }
        CheckBox {
            checked: false;
            Layout.fillWidth: true;
            text: "Load ZCheckBox"
            onCheckStateChanged: {
                if(checked){
                    commonLoader.active=true;
                    commonLoader.source = "CheckBoxTest.qml";
                }
                else
                    commonLoader.active=false;
            }
        }
        CheckBox {
            checked: false;
            Layout.fillWidth: true;
            text: "Load ZRadioButton"
            onCheckStateChanged: {
                if(checked){
                    commonLoader.active=true;
                    commonLoader.source = "RadioButtonTest.qml";
                }
                else
                    commonLoader.active=false;
            }
        }
        CheckBox {
            checked: false;
            Layout.fillWidth: true;
            text: "Load ZvKeyboard"
            onCheckStateChanged: {
                if(checked){
                    commonLoader.active=true;
                    commonLoader.source = "ZvKeyboardTest.qml";
                }
                else
                    commonLoader.active=false;
            }
        }
        CheckBox {
            checked: false;
            Layout.fillWidth: true;
            text: "Load TimedateSetter"
            onCheckStateChanged: {
                if(checked){
                    commonLoader.active=true;
                    commonLoader.source = "TimeDateSetter.qml";
                }
                else
                    commonLoader.active=false;
            }
        }
        CheckBox {
            checked: false;
            Layout.fillWidth: true;
            text: "Load ChartItem"
            onCheckStateChanged: {
                if(checked){
                    commonLoader.active=true;
                    commonLoader.source = "ChartItemTest.qml";
                }
                else
                    commonLoader.active=false;
            }
        }

        // Next CheckBox here

    }

}


