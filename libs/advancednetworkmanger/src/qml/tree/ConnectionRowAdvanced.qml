import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls.Material 2.14
import anmsettings 1.0
import ZeraFa 1.0
import ZeraComponentsConfig 1.0
import ZeraComponents 1.0

Item{
    id: rootItm
    property int type_
    property string groupe_
    property string name_
    property bool available_
    property int signals_
    property var devices_
    property var deviceNames_
    property bool stored_: nmPath !== ""

    property bool connected_
    property string nmPath_
    property string ipv4_

    onConnected_Changed: {
        actswitch.checked = connected_;
        if(connected_){
            actswitch.position=1
        }else{
            actswitch.position=0
        }
        actswitch.visible = true
        actbusyind.visible = false
    }

    function cancelConnect(){
        actswitch.visible = true
        actbusyind.visible = false
         actswitch.checked = connected_;
        if(connected_){
            actswitch.position=1
        }else{
            actswitch.position=0
        }
    }


    signal edit(string p_path)
    signal remove(string p_path)
    signal activate(string p_path, string device)
    signal deactivate(string p_path)

    MouseArea{
        id: itemMouseArea
        anchors.fill: parent
        onClicked: {
            list.currentIndex = index

        }
    }
    RowLayout{
        anchors.fill: parent
        // connection name
        Row {
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Label{
                id: conname
                anchors.verticalCenter: parent.verticalCenter
                text:
                {
                    if(rootItm.connected_ === true)
                        rootItm.name_ + " (" + ipv4_ +")"
                    else
                        rootItm.name_
                }
                font.pixelSize: parent.width / 25
            }
        }
        // select-device-combo (visible only if more than one device is available)
        ComboBox{
            id: devices
            enabled:{
                if(rootItm.connected_ === true){
                    return false;
                }
                return true
            }
            Layout.fillHeight: true
            visible: count >= 2
            Layout.preferredWidth: rootItm.width/5
            model: rootItm.deviceNames_
        }
        // switch to activate/deactivae connection
        Item {
            Layout.preferredWidth: rootItm.width/10
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            ZSwitch {
                id: actswitch
                height: rootItm.height
                width: rootItm.width
                enabled: rootItm.available_
                onClicked: {
                    if(position > 0.5) {
                        position=0.5
                        activate(rootItm.nmPath_,rootItm.devices_[devices.model[devices.currentIndex]]);
                    } else {
                        position=0
                        deactivate(rootItm.nmPath_);
                    }
                    actswitch.visible = false
                    actbusyind.visible = true
                }
            }
            BusyIndicator {
                id: actbusyind
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: rootItm.available_
                visible: false
                height: parent.height
                width: parent.height
                running: visible
           }
        }
        // Signal strenght indicator
        Row {
            Layout.preferredWidth: rootItm.width/10
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            SignalIcon {
                id:signalIcon
                anchors.verticalCenter: parent.verticalCenter
                signals: rootItm.signals_
                width: rootItm.width/33
                height: width
                visible: type_ === 1 && available_
            }
        }
        // edit connection button
        Row {
            Layout.preferredWidth: rootItm.width/10
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            Button {
                id: editButton
                anchors.verticalCenter: parent.verticalCenter
                bottomPadding: ZCC.standardTextBottomMargin
                enabled: rootItm.stored_
                font.pixelSize: rootItm.width/35
                font.family: FA.old
                text: FA.fa_edit
                background: Rectangle  {
                    color: Material.backgroundColor
                }
                onClicked: {
                    edit(rootItm.nmPath_)
                }
            }
        }
        // delete connection button
        Row {
            Layout.preferredWidth: rootItm.width/10
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            Button {
                id: trashButton
                anchors.verticalCenter: parent.verticalCenter
                bottomPadding: ZCC.standardTextBottomMargin
                enabled: rootItm.stored_
                font.pixelSize: rootItm.width/35
                font.family: FA.old
                text: FA.fa_trash
                background: Rectangle{
                    color: Material.backgroundColor
                }
                onClicked: {
                    remove(rootItm.nmPath_)
                }
            }
        }
    }
}

