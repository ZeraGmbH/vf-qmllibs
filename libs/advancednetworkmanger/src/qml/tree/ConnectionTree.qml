import QtQuick 2.14
import QtQuick.Controls 2.14
import SortFilterProxyModel 0.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.12
import ZeraFa 1.0
import anmsettings 1.0
import ZeraTranslation 1.0
import ZeraComponents 1.0
import "../settings"

Pane {
    id: rootItm
    padding: 0

    ConnectionTreeInterface{
        id: backend;
        onAuthFailed: {
            smartConnectLoader.ssid = name;
            smartConnectLoader.device = device;
            smartConnectLoader.path = path;
            smartConnectLoader.active=false;
            smartConnectLoader.newCon=false;
            smartConnectLoader.active=true;
        }
    }
    // Ethernet settings component - ethLoader is consumer
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
        }
    }
    // Wifi settings component - wifiLoader is consumer
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
        }
    }
    // Connection info component - infoLoader is consumer
    Component{
        id: infotab
        ConnectionInfo {
            visible: true
            z: 10
        }
    }
    // Password input component - smartConnectLoader is consumer
    Component {
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
    // Ethernet settings tab loader
    Loader {
        id: ethLoader
        anchors.fill: parent
        anchors.margins: 0
        active : false
        z: 10
        sourceComponent: ethtab
        property string path: ""

        function load(path) {
            infoLoader.active = false;
            ethLoader.path = path
            ethLoader.active = true
        }
        onLoaded: {
            item.path = ethLoader.path
            item.init();
        }
    }
    // Wifi settings tab loader
    Loader{
        id: wifiLoader
        anchors.fill: parent
        anchors.margins: 0
        visible: true
        active : false
        z: 10
        sourceComponent: wifitab
        property string path: ""
        property bool hotspot: true

        function load(path, hotspot) {
            infoLoader.active = false;
            wifiLoader.path = path
            wifiLoader.hotspot = hotspot
            wifiLoader.active = true
        }
        onLoaded: {
            item.path = wifiLoader.path
            item.hotspot = wifiLoader.hotspot
            item.init();
        }
    }
    // Info tab loader
    Loader{
        id: infoLoader
        anchors.top: parent.top
        anchors.bottom: addbutton.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 0
        visible: true
        active : false
        z: 10
        sourceComponent: infotab
    }
    // Password tab loader (SmartConnect: connect to an unsaved SSID)
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
        property bool newCon: true
        property Item rowObject: null
        onLoaded: {
            item.init(ssid,device,path,newCon,rowObject)
        }
    }
    // Section heading component (Ethernet/Wifi/Hotspot...) see ListView
    // section bindings below
    Component {
        id: sectionHeading
        Item {
            id: rect
            width: list.width
            height: rootItm.height/15
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
                    // Notes on translation:
                    // * Strings are bound to groupe role (see ListView section bindings below).
                    // * groupe role is mapped to C++ ConnectionModel role GroupeRole (see ConnectionModel::roleNames).
                    // * GroupeRole role is mapped to ConnectionItem::Groupe member
                    // * ConnectionItem::Groupe are finally set in ::CreateConItem overrides.
                    //
                    // Long talk short result:
                    // * The possible contents are in capital letters (to avoid double translation efforts matching texts
                    //   are kept in all captal letters)
                    // * Supported values are at the time of writing: ETHERNET/HOTSPOT/WIFI
                    text: Z.tr(section)
                    font.bold: true
                    font.pixelSize: parent.width/45
                    Layout.fillWidth: true
                }
            }
        }
    }
    // THE list of connections with separated sections
    ListView {
        id: list
        anchors.top: parent.top
        anchors.bottom: addbutton.top
        anchors.left: parent.left
        anchors.right: parent.right
        clip: true
        spacing: parent.height /50

        model: SortFilterProxyModel{
            sourceModel: backend.dataList
            sorters: StringSorter { roleName: "groupe" }
        }
        delegate: ConnectionRowAdvanced {
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
            ipv4_: ipv4
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: parent.width/30
            height: list.height / 15
            // Action handlers
            onEdit: (path) => {
                if(groupe_ == "ETHERNET") {
                    ethLoader.load(path)
                }
                else if(groupe_ === "WIFI") {
                    wifiLoader.load(path, false)
                }
                else if(groupe_ === "HOTSPOT"){
                    wifiLoader.load(path, true)
                }
            }
            onRemove: (path) => {
                backend.removeConnection(path)
            }
            onActivate: (path, device) => {
                if(!stored_ && device !== "") {
                    smartConnectLoader.rowObject=this
                    smartConnectLoader.ssid = name_
                    smartConnectLoader.device = device
                    smartConnectLoader.path = path
                    smartConnectLoader.newCon=true
                    smartConnectLoader.active=true
                }
                else if(device !== "")
                    backend.connect(path, device)
            }
            onDeactivate: (path) => {
                backend.disconnect(path)
            }
        }
        // ListView section bindings
        section.delegate: sectionHeading
        section.property: "groupe"
        section.criteria: ViewSection.FullString

        boundsBehavior: Flickable.StopAtBounds
        ScrollIndicator.vertical: ScrollIndicator {
            id: scroller
            active: true
            onActiveChanged: {
                if(active !== true) {
                    active = true;
                }
            }
        }
    }
    readonly property real buttonPointSize: height>0 ? height * 0.055 : 10
    readonly property real buttonVerticalPadding: buttonPointSize * 0.33
    ZButton {
        id: addbutton
        text: "+"
        font.pointSize: buttonPointSize
        onClicked: menu.open()
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        verticalPadding: buttonVerticalPadding
        width: implicitHeight * 1.25
        Menu {
            id: menu
            MenuItem {
                text: Z.tr("Add Ethernet...")
                onClicked: ethLoader.load("")
            }
            MenuSeparator { }
            MenuItem {
                text: Z.tr("Add Hotspot...")
                onClicked: wifiLoader.load("", true)
            }
            MenuSeparator { }
            MenuItem {
                text: Z.tr("Add Wifi...")
                onClicked: wifiLoader.load("", false)
            }
        }
    }
    ZButton {
        id: infoButton
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        font.family: FA.old
        font.pointSize: buttonPointSize
        verticalPadding: buttonVerticalPadding
        width: implicitHeight * 1.25
        text: {
            let ret = FA.fa_info_circle
            if(infoLoader.active) {
                let colorPrefix = "<font color='" + Qt.lighter(Material.color(Material.Amber)) + "'>"
                let colorPostfix = "</font>"
                ret = colorPrefix + ret + colorPostfix
            }
            return ret
        }
        onClicked: {
            infoLoader.active = !infoLoader.active
        }
    }
}
