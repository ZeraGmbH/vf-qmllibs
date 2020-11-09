import QtQuick 2.0

import QtQuick 2.0

import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

import advancednetworkmanager 1.0
import notificationmanager 1.0


import "qrc:/"
//import "qrc:/src/qml/advancednetworkmanager/"
//import "qrc:/src/qml/advancednetworkmanager/tree"
//notificationmanager
import "qrc:/src/qml"

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "networkmanager"


    // resolution the gui was designed with
    readonly property int defWidth : 800
    readonly property int defHeight : 400

    width: 800
    height: 480


    property int count: 0

    NotificationManager {
            id: notificationManager
            window: notWindow
            ySpacing: 20
            notificationWidth: 300
            maxOnScreen: 2
            ontime: 3000
            Component.onCompleted: {

            }
        }


    TabBar {
        id: bar
        width: parent.width
        anchors.top: parent.top
        TabButton {
            text: qsTr("Networksettings")
        }
    }


    StackLayout
    //SwipeView
    {
        id: stack
        currentIndex: bar.currentIndex
        anchors.top: bar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 0

        NetworkManager{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 0
            onNotification: {
                notificationManager.notify(title,msg);
            }
        }
    }

    Item {
            id: notWindow
            anchors.top: parent.top
            width: parent.width
            height: parent.height-45
        }



}


