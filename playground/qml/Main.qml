import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Controls.Material 2.12
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
                    commonLoader.source = "SimpleAndCheapVuTest.qml";
                }
                else
                    commonLoader.active=false;
            }
        }
        CheckBox {
            id: shownuiv
            checked: false;
            Layout.fillWidth: true;
            text: "Load uivector"
            onCheckStateChanged: {
                if(checked){
                    commonLoader.active=true;
                    commonLoader.source = "Uivectorgraph.qml";
                }else{
                    commonLoader.active=false;
                }
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
                    commonLoader.source = "ZvKeyboard.qml";
                }
                else
                    commonLoader.active=false;
            }
        }

        // Next CheckBox here

    }

}


