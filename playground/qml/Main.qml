import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12


import "qrc:/"

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "playground"

    width: 400
    height: 600

    // Add your Playground here

    Loader {
        id: netLoader
        anchors.left: mainWindow.right
        anchors.top: mainWindow.top
    }


    Loader {
        id: compLoader
        anchors.left: mainWindow.right
        anchors.top: mainWindow.top
    }

    Loader {
        id: anmLoader
        anchors.left: mainWindow.right
        anchors.top: mainWindow.top
    }

    Loader {
        id: notifiLoader
        anchors.left: mainWindow.right
        anchors.top: mainWindow.top
    }

    Loader {
        id: uivLoader
        anchors.left: mainWindow.right
        anchors.top: mainWindow.top
    }

    //Next Loader here

    GridLayout{
        anchors.fill: parent
        columns: 2

        CheckBox{
            id: showanmsettings
            checked: false;
            Layout.fillWidth: true;
            text: "Load anmsettings"
            Component.onCompleted: {
                if(checked){
                    anmLoader.active=true;
                    anmLoader.source = "Anmsettings.qml";
                }else{
                    anmLoader.active=false;
                }
            }
            onCheckStateChanged: {
                if(checked){
                    anmLoader.active=true;
                    anmLoader.source = "Anmsettings.qml";
                }else{
                    anmLoader.active=false;
                }
            }
        }

        CheckBox{
            id: shownotifmanager
            checked: false;
            Layout.fillWidth: true;
            text: "Load notifiManager"
            Component.onCompleted: {
                if(checked){
                    notifiLoader.active=true;
                    notifiLoader.source = "notifiManager.qml";
                }else{
                    notifiLoader.active=false;
                }
            }
            onCheckStateChanged: {
                if(checked){
                    notifiLoader.active=true;
                    notifiLoader.source = "notifiManager.qml";
                }else{
                    notifiLoader.active=false;
                }
            }
        }

        CheckBox{
            id: shownuiv
            checked: false;
            Layout.fillWidth: true;
            text: "Load uivector"
            Component.onCompleted: {
                if(checked){
                    uivLoader.active=true;
                    uivLoader.source = "Uivectorgraph.qml";
                }else{
                    uivLoader.active=false;
                }
            }
            onCheckStateChanged: {
                if(checked){
                    uivLoader.active=true;
                    uivLoader.source = "Uivectorgraph.qml";
                }else{
                    uivLoader.active=false;
                }
            }
        }

        // Next CheckBox here

    }

}


