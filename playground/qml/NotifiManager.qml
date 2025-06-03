import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.12
import Notifications 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "notificationmanager"
    width: 800
    height: 480
    property int count: 0

    NotificationManager {
        id: notificationManager
        window: notWindow
        ySpacing: 20
        notificationWidth: 300
        maxOnScreen: 20
    }
    Item {
        id: notWindow
        anchors.top: parent.top
        width: parent.width
        height: parent.height

        Button {
            id: dyn
            text: "Dynamic"
            onClicked: {
                notificationManager.notify("Btn1","Hello das ist ein test blub blub blub" + count);
                count = count + 1 ;
            }
        }
        Button {
            id: dyn2
            text: "Dynamic"
            anchors.left: dyn.right
            onClicked: {
                notificationManager.notify("Btn2","Hello das ist ein test blub blub blub \n \n \n Hallo again" + count);
                count = count + 1 ;
            }
        }
        Button {
            id: dyn3
            text: "Close"
            anchors.left: dyn2.right
            onClicked: {
                notificationManager.close()
            }
        }
    }
}


