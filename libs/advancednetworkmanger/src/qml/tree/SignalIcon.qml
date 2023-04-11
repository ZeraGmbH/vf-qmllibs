import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
Item{
    id: rootItm
    property int signals : 0
    Row{
        anchors.fill: parent
        spacing: parent.width/10
        Rectangle{
            width: parent.width/3-2
            height: parent.height/3
            anchors.bottom: parent.bottom
            border.color: "white"
            color: {
                if(rootItm.signals > 30){
                    return "white"
                }else{
                    return "transparent"
                }
            }
        }
        Rectangle{
            width: parent.width/3-2
            height: parent.height/3*2
            anchors.bottom: parent.bottom
            border.color: "white"
            color: {
                if(rootItm.signals > 60){
                    return "white"
                }else{
                    return "transparent"
                }
            }
        }
        Rectangle{
            width: parent.width/3-2
            height: parent.height
            anchors.bottom: parent.bottom
            border.color: "white"
            color: {
                if(rootItm.signals > 95){
                    return "white"
                }else{
                    return "transparent"
                }
            }
        }
    }
}
