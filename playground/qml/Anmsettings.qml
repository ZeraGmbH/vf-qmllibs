import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import anmsettings 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "networkmanager"

    width: 800
    height: 480

    TabBar {
        id: bar
        width: parent.width
        anchors.top: parent.top
        TabButton {
            text: qsTr("Networksettings")
        }
    }

    StackLayout
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
            //Layout.margins: 0
            onNotification: {
               // notificationManager.notify(title,msg);
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
