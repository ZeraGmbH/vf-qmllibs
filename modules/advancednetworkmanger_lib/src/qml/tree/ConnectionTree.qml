import QtQuick 2.0
import QtQuick.Controls 2.12
import SortFilterProxyModel 0.2
import QtQuick.Layouts 1.12
import ZeraFa 1.0
import anmsettings 1.0
import "qrc:/src/qml/settings"

Pane {
    id: rootItm
    padding: 0

    signal notification(string title,string msg);
    ConnectionTreeInterface{
        id: backend;
    }
    Component{
        id: ethtab
        EthernetSettings{
            anchors.fill: parent
            anchors.margins: 0
            visible: true
            z: 10
            onVisibleChanged: {
                if(!visible){
                    ethLoader.active = false;
                }
            }
            onNotification: {
                rootItm.notification(title,msg);
            }
        }
    }
    Component{
        id: wifitab
        WifiSettings {
            anchors.fill: parent
            anchors.margins: 0
            visible: true
            z: 10
            onVisibleChanged: {
                if(!visible) {
                    wifiLoader.active = false;
                }
            }
            onNotification: {
                rootItm.notification(title,msg);
            }
        }
    }

    Component{
        id: infotab
        ConnectionInfo {
            anchors.top: parent.top
            anchors.bottom: showall.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 0
            visible: true
            z: 10
        }
    }

    Component{
        id: pwDialog
        SmartConnect{
            width: parent.width
            visible: true
            onVisibleChanged: {
                if(!visible){
                    smartConnectLoader.active = false;
                }
            }
        }
    }

    Loader {
        id: ethLoader
        anchors.fill: parent
        anchors.margins: 0
        active : false
        z: 10
        sourceComponent: ethtab
        property string path: ""
        onLoaded: {
            item.path = ethLoader.path
            item.init();
        }
        onActiveChanged: {
            if(!active) {
                path = "";
            }
        }
    }

    Loader{
        id: wifiLoader
        anchors.fill: parent
        anchors.margins: 0
        visible: true
        active : false
        z: 10
        sourceComponent: wifitab
        property string path: ""
        onLoaded: {
            item.path = wifiLoader.path
            item.init();
        }
        onActiveChanged: {
            if(!active){
                path = "";
            }
        }
    }

    Loader{
        id: infoLoader
        anchors.top: parent.top
        anchors.bottom: showall.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 0
        visible: true
        active : false
        z: 10
        sourceComponent: infotab
    }

    Loader {
        id: smartConnectLoader
        width: parent.width*0.9
        anchors.top: parent.top
        parent: Overlay.overlay
        z: 10
        active : false
        visible: true
        sourceComponent: pwDialog
        property string ssid: ""
        property string device: ""
        property string path: ""
        onLoaded: {
            item.init(ssid,device,path)
        }
    }

    Component {
        id: sectionHeading
        Item{
            id: rect
            width: list.width
            height: 15
            anchors.margins: 0
            RowLayout{
                anchors.fill: parent
                anchors.margins: 0
                Layout.margins: 0
                spacing: 0
                Label {
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignVCenter
                    id: secLab
                    text: section
                    font.bold: true
                    font.pixelSize: 14
                    Layout.fillWidth: true
                }

            }
        }
    }
    ListView{
        id: list
        anchors.top: parent.top
        anchors.bottom: showall.top
        anchors.left: parent.left
        anchors.right: parent.right
        clip: true
        spacing: 10

        model: SortFilterProxyModel{
            sourceModel: backend.dataList
            filters:[
                RegExpFilter{
                    enabled: showall.checked
                    roleName: "nmPath"
                    pattern: "[A-Za-z0-9,-_.\s]+"
                    caseSensitivity: Qt.CaseInsensitive
                },
                RegExpFilter{
                    enabled: true
                    inverted: false
                    roleName: "name"
                    pattern: ""
                    caseSensitivity: Qt.CaseInsensitive
                }
                ,
                ValueFilter{
                    enabled: !showall.checked
                    roleName: "available"
                    value: 1
                },
                AnyOf{
                    RegExpFilter {
                        enabled: vpnshow.checked
                        roleName: "groupe"
                        pattern: "VPN"
                        caseSensitivity: Qt.CaseInsensitive
                    }
                    RegExpFilter {
                        enabled: apshow.checked
                        roleName: "groupe"
                        pattern: "HOTSPOT"
                        caseSensitivity: Qt.CaseInsensitive
                    }
                    RegExpFilter {
                        enabled: wifishow.checked
                        roleName: "groupe"
                        pattern: "WIFI"
                        caseSensitivity: Qt.CaseInsensitive
                    }
                    RegExpFilter {
                        enabled: ethshow.checked
                        roleName: "groupe"
                        pattern: "ETHERNET"
                        caseSensitivity: Qt.CaseInsensitive
                    }

                }
            ]
            sorters: StringSorter { roleName: "groupe" }
        }
        delegate: ConnectionRowAdvanced{
            name_: name
            available_: available
            type_: type
            signals_: signalStrength
            groupe_: groupe
            connected_: connected
            nmPath_: nmPath
            devices_: devices
            deviceNames_: deviceNames
            stored_: stored
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: parent.width/30
            height: 30

            onEdit: {
                if(groupe_ == "ETHERNET") {
                    ethLoader.path = p_path;
                    ethLoader.active = true;
                } else if(groupe_ === "WIFI"){
                    wifiLoader.path = p_path;
                    wifiLoader.active = true;

                } else if(groupe_ === "HOTSPOT"){
                    wifiLoader.path = p_path;
                    wifiLoader.active = true;
                }
            }

            onRemove: {
                backend.removeConnection(p_path)
            }

            onActivate: {
                var Device = device;
                if(!stored_ && Device !== "") {
                  //  Device= device
                    smartConnectLoader.ssid = name_;
                    smartConnectLoader.device = Device;
                    smartConnectLoader.path = p_path;
                    smartConnectLoader.active=true;
                } else if(Device !== "") {

                    backend.connect(p_path,Device);
                }

            }
            onDeactivate: {
                backend.disconnect(p_path)
            }

            onNotification: {
                rootItm.notification(title,msg);
            }
        }

        section.delegate: sectionHeading
        section.property: "groupe"
        section.criteria: ViewSection.FullString

        boundsBehavior: Flickable.StopAtBounds
        ScrollIndicator.vertical: ScrollIndicator {
            id: scroller
            active: true
            onActiveChanged: {
                if(active !== true)
                {
                    active = true;
                }
            }
        }
    }

    Button {
        id: addbutton
        text: "+"
        onClicked: menu.open()
        anchors.top: showall.top
        anchors.left: parent.left
        anchors.bottom: showall.bottom
        Menu {
            id: menu
            title: "+"
            MenuItem {
                text: "+ ETHERNET"
                onClicked: {
                    infoLoader.active = false;
                    ethLoader.active = true;
                }
            }
            MenuItem {
                text: "+ WIFI"
                onClicked: {
                    infoLoader.active = false;
                    wifiLoader.active = true;
                }
            }
        }
    }
    CheckBox{
        id: showall
        anchors.bottom: parent.bottom
        anchors.left: addbutton.right
        text: "SHOW ALL"
    }
    CheckBox{
        anchors.right: wifishow.left
        anchors.bottom: parent.bottom
        id: ethshow
        checked: true
        text: "ETHERNET"
    }

    CheckBox{
        anchors.right: apshow.left
        anchors.bottom: parent.bottom
        id: wifishow
        checked: true
        text: "WIFI"
    }

    CheckBox{
        anchors.right: infoButton.left
        anchors.bottom: parent.bottom
        id: apshow
        checked: true
        text: "HOTSPOT"
    }

    CheckBox{
        anchors.right: blueshow.left
        anchors.bottom: parent.bottom
        id: vpnshow
        checked: false
        visible: false
        text: "VPN"
    }

    CheckBox{
        anchors.right: infoButton.left
        anchors.bottom: parent.bottom
        id: blueshow
        checked: false
        visible: false
        text: "BLUETOOTH"
    }
    Button{
        id: infoButton
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        font.family: FA.old
        text: FA.icon(FA.fa_info,null);
        font.pixelSize: 18
        background: Rectangle{
            color: "transparent"
        }
        onClicked: {
            if(infoLoader.active === false){
                infoLoader.active = true;
            } else {
                infoLoader.active = false;
            }

        }
    }
}



