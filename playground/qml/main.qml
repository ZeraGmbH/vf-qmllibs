import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12


//Do not import custom stuff here

// Load our plugin from filesystem
import "qrc:/"

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "playground"

    width: 400
    height: 600

    // Add your Playground here

    /* Create an ApplicationWindow Item
    *  then add a loader and checkbox. Load your start window
    *  if the checkbox is chekced.Unload it when unchecked. Loading the Files with the checkbox will prevent
    *  the playground to crash because of other projects.
    */



    Loader {
        id: compLoader
        anchors.left: mainWindow.right
        anchors.top: mainWindow.top
    } //Networksettings Loader




    Loader {
        id: anmLoader
        anchors.left: mainWindow.right
        anchors.top: mainWindow.top
    } //anmsettings Loader

    Loader {
        id: notifiLoader
        anchors.left: mainWindow.right
        anchors.top: mainWindow.top
    } //anmsettings Loader

    Loader {
        id: uivLoader
        anchors.left: mainWindow.right
        anchors.top: mainWindow.top
    } //anmsettings Loader

    //Next Loader here

    GridLayout{
        anchors.fill: parent
        columns: 2

        //Networkcomponents checkbox



        CheckBox{
            id: showzeracomps
            checked: false;
            Layout.fillWidth: true;
            text: "Load zeraComp"
            Component.onCompleted: {
                if(checked){
                    compLoader.active=true;
                    compLoader.source = "zeracomps.qml";
                }else{
                    compLoader.active=false;
                }
            }
            onCheckStateChanged: {
                if(checked){
                    compLoader.active=true;
                    compLoader.source = "zeracomps.qml";
                }else{
                    compLoader.active=false;
                }
            }
        }

        CheckBox{
            id: showanmsettings
            checked: false;
            Layout.fillWidth: true;
            text: "Load anmsettings"
            Component.onCompleted: {
                if(checked){
                    anmLoader.active=true;
                    anmLoader.source = "anmsettings.qml";
                }else{
                    anmLoader.active=false;
                }
            }
            onCheckStateChanged: {
                if(checked){
                    anmLoader.active=true;
                    anmLoader.source = "anmsettings.qml";
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
                    uivLoader.source = "uivectorgraph.qml";
                }else{
                    uivLoader.active=false;
                }
            }
            onCheckStateChanged: {
                if(checked){
                    uivLoader.active=true;
                    uivLoader.source = "uivectorgraph.qml";
                }else{
                    uivLoader.active=false;
                }
            }
        }

        // Next CheckBox here

    }

}


