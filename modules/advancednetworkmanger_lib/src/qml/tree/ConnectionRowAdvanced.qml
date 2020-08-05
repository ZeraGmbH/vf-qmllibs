import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import anmsettings 1.0
import ZeraFa 1.0

Item{
    id: rootItm
    property int type_
    property string groupe_
    property string name_
    property bool available_
    property int signals_
    property var devices_
    property var deviceNames_
    property bool stored_ : {
        if(nmPath === "") {
            return false;
        } else {
            return true;
        }
    }

    property bool connected_
    property string nmPath_

    onConnected_Changed: {
        actswitch.checked = connected_;
    }

    signal edit(string p_path)
    signal remove(string p_path)
    signal activate(string p_path, string device)
    signal deactivate(string p_path)
    signal notification(string title,string msg);

    MouseArea{
        id: itemMouseArea
        anchors.fill: parent
        onClicked: {
            list.currentIndex = index

        }
    }

    RowLayout{
        anchors.fill: parent

        Row{
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Label{
                anchors.verticalCenter: parent.verticalCenter
                id: conname
                text: rootItm.name_
            }
        }

        ComboBox{
            id: devices
            Layout.fillHeight: true
            property string dev : model[currentIndex]
            visible: {
                if(count < 2){
                    return false;
                } else {
                    return true;
                }
            }

            Layout.preferredWidth: rootItm.width/5
            model: rootItm.deviceNames_
        }

        Row{
            Layout.preferredWidth: rootItm.width/10
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            Switch {
                anchors.verticalCenter: parent.verticalCenter
                enabled: rootItm.available_
                id: actswitch
                position: {
                    if (rootItm.connected_ === true){
                        return 1;
                    } else {
                        return 0;
                    }
                }

                checked : rootItm.connected_
                onClicked: {
                    if(position === 1){
                        activate(rootItm.nmPath_,rootItm.devices_[devices.model[devices.currentIndex]]);
                        //position = 0;
                        checked = rootItm.connected_
                    } else {
                        deactivate(rootItm.nmPath_);
                        //position = 1;
                        checked = rootItm.connected_
                    }
                }
            }
        }
        Row {
            Layout.preferredWidth: rootItm.width/10
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter

            SignalIcon{
                anchors.verticalCenter: parent.verticalCenter
                signals: rootItm.signals_
                width: 20
                height: 20
                visible: {
                    if(type_ === 1 && available_) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }

            Rectangle{
                anchors.verticalCenter: parent.verticalCenter
                width: 20
                height: 20
                color: "transparent"
                visible: {
                    if(type_ !== 1 || !available_){
                        return true;
                    } else{
                        return false;
                    }
                }
            }
        }

        Row {
            Layout.preferredWidth: rootItm.width/10
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            Button{
                anchors.verticalCenter: parent.verticalCenter
                id: edbutton
                enabled: rootItm.stored_
                font.pixelSize: 18
                font.family: FA.old
                text: FA.icon(FA.fa_edit,null)
                background: Rectangle{
                    color: "transparent"
                }
                onClicked: {
                    edit(rootItm.nmPath_)
                }
            }
        }

        Row {
            Layout.preferredWidth: rootItm.width/10
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            Button{
                anchors.verticalCenter: parent.verticalCenter
                enabled: rootItm.stored_
                font.pixelSize: 18
                font.family: FA.old
                text: FA.icon(FA.fa_trash,null)
                background: Rectangle{
                    color: "transparent"
                }
                onClicked: {
                    remove(rootItm.nmPath_)
                }
            }
        }
    }
}

