import QtQml 2.2
import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

QtObject {
    id: base
    property int x: 0
    property var window
    property var listOfNotifications: []
    property var queue: []
    property int  maxOnScreen: 3
    property int ySpacing: 5
    property int notificationWidth: 150

    function timerObj() {
        return Qt.createQmlObject("import QtQuick 2.0; Timer {}", appWindow);
    }

    function notify(title, Message){
        // Add message to queue
        base.queue.unshift({head: title, msg: Message});
        if(maxOnScreen>listOfNotifications.length){
            tryNotify();
        }
    }

    function sortOnScreen(index){
        if(index>=0){
            if(listOfNotifications.length>index){

                listOfNotifications[index].y = window.height-listOfNotifications[index].implicitHeight
                listOfNotifications[index].z = listOfNotifications.length
                listOfNotifications[index].x = window.width-notificationWidth
            }
            for (var i = index+1;i<listOfNotifications.length;i++){
                listOfNotifications[i].y = listOfNotifications[i-1].y - ySpacing
                if (listOfNotifications[i].y === 0){
                    listOfNotifications[i].y = window.height-listOfNotifications[i].height
                }
                listOfNotifications[i].z = listOfNotifications.length-i
                listOfNotifications[i].x=window.width-notificationWidth
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
        listOfNotifications.push(notifi);
        notifi.open();
        sortOnScreen(0);
        notifi.closed.connect( function closingPopup(){
            var index = listOfNotifications.indexOf(notifi);
            if (index > -1){
                listOfNotifications.splice(index, 1);
            }
            notifi.destroy();
            if(listOfNotifications.length > 0){
                sortOnScreen(index);
            }
            if(base.queue.length>0)tryNotify();
        })
    }

    function close(){
        while(listOfNotifications.length > 0) {
            var window = listOfNotifications.pop();
            window.destroy();
        }
    }
}
