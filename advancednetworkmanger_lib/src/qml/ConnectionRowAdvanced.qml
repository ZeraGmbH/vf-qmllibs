import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

import "qrc:/src/qml/FontAwesome.js" as FS



Item{
    id: rootItm
    property int type_
    property string groupe_
    property string name_
    property bool active_
    property int signals_
    property bool stored_ : {
        if(nmPath === ""){
            return false;
        }else{
            return true;
        }
    }

    property bool connected_
    property string nmPath_

    signal edit(string p_name)
    signal remove(string p_name)
    signal activate(string p_name)

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
        Row{
            Layout.preferredWidth: rootItm.width/8
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            Switch {
                anchors.verticalCenter: parent.verticalCenter
                enabled: rootItm.active_
                id: actswitch
                position: {
                    if (rootItm.connected_ === true){
                        return 1;
                    }else{
                        return 0;
                    }
                }

                onClicked: {
                    if(position === 1){
                        activate(rootItm.name_)
                        notification("NM   " + FS.icon(FS.fa_chain,null), "connection with network etablished")
                    }else{
                        notification("NM   " + FS.icon(FS.fa_chain_broken,null), "disconnected from network")
                    }
                }
            }

        }
        Row{
            Layout.preferredWidth: rootItm.width/8
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            SignalIcon{
                anchors.verticalCenter: parent.verticalCenter
                signals: rootItm.signals_
                width: 20
                height: 20
                visible: {
                    if(type_ === 2 && active_){
                        return true;
                    }else{
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
                    if(type_ !== 2 || !active_){
                        return true;
                    }else{
                        return false;
                    }
                }


            }

        }

        Row{
            Layout.preferredWidth: rootItm.width/8
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            Button{
                anchors.verticalCenter: parent.verticalCenter
                id: edbutton
                enabled: rootItm.stored_
                text: FS.icon(FS.fa_edit,null)
                background: Rectangle{
                    color: "transparent"
                }

            }
        }

        Row{
            Layout.preferredWidth: rootItm.width/8
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            Button{
                anchors.verticalCenter: parent.verticalCenter
                enabled: rootItm.stored_
                text: FS.icon(FS.fa_trash,null)
                background: Rectangle{
                    color: "transparent"
                }
            }
        }


    }




}

