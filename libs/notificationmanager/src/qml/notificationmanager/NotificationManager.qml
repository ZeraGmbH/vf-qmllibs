import QtQml 2.2
import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

//import PQML.Controls 1.0 as PC

QtObject {
    id: base
    property int x: 0
    property var window

    property var notifications: []
    property var queue: []
    property int  maxOnScreen: 3


    property int ySpacing: 5
    property int notificationWidth: 150
    property int  ontime: 1000

    function timerObj() {
        return Qt.createQmlObject("import QtQuick 2.0; Timer {}", appWindow);
    }

    function notify(title, Message){
        // Add message to queue
        base.queue.unshift({head: title, msg: Message});
        if(maxOnScreen>notifications.length){
            tryNotify();
        }
    }

    function sortOnScreen(index){
        if(index>=0){
        if(notifications.length>index){

            notifications[index].y = window.height-notifications[index].implicitHeight
            notifications[index].z = notifications.length
            notifications[index].x = window.width-notificationWidth
        }

        for (var i = index+1;i<notifications.length;i++){
            notifications[i].y = notifications[i-1].y - ySpacing
                        if (notifications[i].y === 0){
                            notifications[i].y = window.height-notifications[i].height
                        }
            notifications[i].z = notifications.length-i
            notifications[i].x=window.width-notificationWidth
        }
        }
    }

    function tryNotify(){
        var notedata = base.queue.pop();
        var message = notedata.msg;
        var title = notedata.head;
        var component = Qt.createComponent("Notification.qml");
        var notifi = component.createObject(window,{});
        notifi.text =  message;
        notifi.title =  title;
        notifi.width = notificationWidth;
        notifi.y=window.height;



        notifications.push(notifi);
        if(popupTimer.running === false){
            popupTimer.running = true
        };
        notifi.open();
        sortOnScreen(0);
        notifi.closed.connect( function closingPopup(){
            var index = notifications.indexOf(notifi);
            if (index > -1){
                notifications.splice(index, 1);
            }
            notifi.destroy();
            if(notifications.length > 0){
                sortOnScreen(index);
                popupTimer.running = true;
            }
            if(base.queue.length>0)tryNotify();
        })
    }

    property var popupTimer: Timer{
        interval: ontime// milliseconds
        running: false
        repeat: false
        onTriggered: {
            if(notifications.length > 0){
                notifications[0].close()
            }
        }
    }

}
