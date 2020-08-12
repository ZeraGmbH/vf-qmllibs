import QtQuick 2.0

import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12
import QtQuick.VirtualKeyboard.Settings 2.2
import anmsettings 1.0
import ZeraFa 1.0
import ZeraLocale 1.0
import ZeraComponents 1.0

Pane {
    id: rootItm
    padding: 0
    topPadding: 5
    property string path : ""

    signal notification(string title,string msg);

    function init() {
        if(path === "") {
            backend.create();
        } else {
            backend.load(path);
        }
    }
    NetworkmanagerAbstraction {
        id: generalbackend
    }
    WiredConnectionSettingsInterface {
        id: backend
        onLoadComplete: {
            name.text = backend.conName;
            if(backend.ipv4Mode === "DHCP") {
                ipv4Mode.currentIndex = 0
            } else if(backend.ipv4Mode === "MANUAL"){
                ipv4Mode.currentIndex = 1
            }
            ipv4.text = backend.ipv4;
            sub4.text = backend.ipv4Sub;
            ipv6.text = backend.ipv6;
            sub6.text = backend.ipv6Sub;
            var index = devices.find(backend.device,Qt.MatchExactly);
            if(index >= 0 ) {
                devices.currentIndex = index;
            } else {
                devices.currentIndex = 0;
            }
            backend.device = devices.model[devices.currentIndex]

            if(backend.ipv6Mode === "DHCP"){
                ipv6Mode.currentIndex = 0
            } else if(backend.ipv6Mode === "MANUAL"){
                ipv6Mode.currentIndex = 1
            }
        }
    }
    VisualItemModel {
        id: clientModel
        readonly property int labelWidth : rootItm.width/4
        readonly property int rowHeight : rootItm.height/12
        property real pointSize: clientModel.rowHeight / 2.8 // reduce ZLineEdit default slightly
        Label {
            id: header
            anchors.left: parent.left
            anchors.right: parent.right
            height: clientModel.rowHeight
            font.pointSize: clientModel.pointSize
            font.bold: true
            horizontalAlignment: Label.AlignHCenter
            text: "Ethernet Connection Settings"
        }
        //--------------------------
        // Connection name area
        ZLineEdit {
            id: name
            anchors.left: parent.left
            anchors.right: parent.right
            height: clientModel.rowHeight
            pointSize: clientModel.pointSize
            description.text: "Connection name"
            description.width: clientModel.labelWidth
            validator: RegExpValidator{ regExp: /.{3,}/ }
            function doApplyInput(newText) {
                backend.conName = newText;
                return true
            }
        }
        //--------------------------
        // IPv4 area
        Label {
            id: ipv4header
            anchors.left: parent.left
            anchors.right: parent.right
            height: clientModel.rowHeight
            font.pointSize: clientModel.pointSize
            font.bold: true
            text: "IPv4"
        }
        RowLayout {
            id: ipv4ModeL
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            Label {
                id: ipv4ModeLabel
                text: "Mode"
                Layout.preferredWidth: clientModel.labelWidth
                font.pointSize: clientModel.pointSize
            }
            ComboBox {
                id: ipv4Mode
                height: clientModel.rowHeight
                Layout.fillWidth: true
                font.pointSize: clientModel.pointSize
                model: ["DHCP", "MANUAL"]
                onCurrentIndexChanged: {
                    backend.ipv4Mode = model[currentIndex]
                }
            }
        }
        ZLineEdit {
            id: ipv4
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            description.text: "IP"
            description.width: clientModel.labelWidth
            height: clientModel.rowHeight
            pointSize: clientModel.pointSize
            validator: RegExpValidator { regExp: /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/}
            enabled: ipv4Mode.currentText !== "DHCP"
            // overrides
            function doApplyInput(newText) {
                backend.ipv4 = newText;
                return true
            }
            function activeFocusChange(actFocus) {
                baseActiveFocusChange(actFocus)
                // hack: force virtual keyboard numeric with decimal point
                textField.inputMethodHints = Qt.ImhFormattedNumbersOnly
                VirtualKeyboardSettings.locale = actFocus ? "en_GB" : ZLocale.localeName
            }
        }
        ZLineEdit {
            id: sub4
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            description.text: "Subnetmask"
            description.width: clientModel.labelWidth
            height: clientModel.rowHeight
            pointSize: clientModel.pointSize
            validator: RegExpValidator { regExp: /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/}
            enabled: ipv4Mode.currentText !== "DHCP"
            // overrides
            function doApplyInput(newText) {
                backend.ipv4Sub = newText;
                return true
            }
            function activeFocusChange(actFocus) {
                baseActiveFocusChange(actFocus)
                // hack: force virtual keyboard numeric with decimal point
                textField.inputMethodHints = Qt.ImhFormattedNumbersOnly
                VirtualKeyboardSettings.locale = actFocus ? "en_GB" : ZLocale.localeName
            }
        }

        //--------------------------
        // IPv6 area
        Label {
            id: ipv6header
            anchors.left: parent.left
            anchors.right: parent.right
            height: clientModel.rowHeight
            font.pointSize: clientModel.pointSize
            font.bold: true
            text: "IPv6"
        }
        RowLayout {
            id: ipv6ModeL
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            Label {
                id: ipv6ModeLabel
                text: "Mode"
                Layout.preferredWidth: clientModel.labelWidth
                font.pointSize: clientModel.pointSize
            }
            ComboBox {
                id: ipv6Mode
                height: clientModel.rowHeight
                Layout.fillWidth: true
                font.pointSize: clientModel.pointSize
                model: ["DHCP", "MANUAL"]
                onCurrentIndexChanged: {
                    backend.ipv6Mode = model[currentIndex]
                }
            }
        }
        ZLineEdit {
            id: ipv6
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            description.text: "IP"
            description.width: clientModel.labelWidth
            height: clientModel.rowHeight
            pointSize: clientModel.pointSize
            validator: RegExpValidator { regExp: /([a-f0-9:]+:+)+[a-f0-9]+/}
            enabled: ipv6Mode.currentText !== "DHCP"
            // overrides
            function doApplyInput(newText) {
                backend.ipv6 = newText;
                return true
            }
        }
        ZLineEdit {
            id: sub6
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            description.text: "Subnetmask"
            description.width: clientModel.labelWidth
            height: clientModel.rowHeight
            pointSize: clientModel.pointSize
            // TODO: This looks like a copy & paste from IPv4
            validator: RegExpValidator { regExp: /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/}
            enabled: ipv6Mode.currentText !== "DHCP"
            // overrides
            function doApplyInput(newText) {
                backend.ipv6Sub = newText;
                return true
            }
        }
    }
    //--------------------------
    // This is the list view for VisualItemModel id:clientModel
    ListView {
        id: list
        anchors.top: parent.top
        anchors.bottom: save.top
        anchors.left: parent.left
        anchors.right: parent.right
        model: clientModel
        clip: true
    }
    //--------------------------
    // Cancel / OK buttons
    ZButton{
        id: save
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        height: clientModel.rowHeight
        text: "OK"
        onClicked: {
            var good = true;
            var errorField;

            if(!ipv6.acceptableInput && ipv6.enabled) {
                good = false;
                errorField="IPV6 IP"
            } else if(!sub6.acceptableInput && sub6.enabled) {
                good = false;
                errorField="IPV6 Subnetmask"
            } else if(!ipv4.acceptableInput &&ipv4.enabled) {
                good = false;
                errorField="IPV4 IP"
            } else if(!sub4.acceptableInput && sub4.enabled) {
                good = false;
                errorField="IPV4 Subnetmask"
            } else if(!name.acceptableInput){
                good = false;
                errorField="Name"
            }
            if(good) {
                backend.save();
                rootItm.visible = false
            } else {
                notification("NM", "invalid settings in field: " + errorField)
            }
        }
    }
    ZButton{
        id: cancel
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: clientModel.rowHeight
        text: "Cancel"
        onClicked: {
            backend.discard();
            rootItm.visible = false
        }
    }
}
