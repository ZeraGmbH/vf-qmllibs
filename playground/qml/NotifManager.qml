import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import NotificationMsgContainer 1.0
import NotificationMsg 1.0
import NotificationMsgExpiring 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "notificationmanager"
    width: 800
    height: 480

    NotificationMsgContainer {
        id: notificationCtr
    }

    NotificationMsg {
        id: notifmsg
        msg: "a"
    }

//    NotificationMsgExpiring{
//        id: notifExpMsg
//        timer: 50
//    }

    Item {
        id: notWindow
        anchors.top: parent.top
        width: parent.width
        height: parent.height

//        Button {
//            id: expmsg
//            text: "expiring msg"
//            onClicked: {
//                notificationCtr.addMsg(notifExpMsg)
//            }
//        }
        Button {
            id: msg
            text: "non-expiring msg"
            anchors.left: expmsg.right
            onClicked: {
                notificationCtr.addMsg(notifmsg)
            }
        }
        Button {
            id: close
            text: "Close"
            anchors.left: msg.right
            onClicked: {
                notificationCtr.clear()
            }
        }
    }
}


