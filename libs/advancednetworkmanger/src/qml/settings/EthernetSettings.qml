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
import ZeraComponentsConfig 1.0
import ZeraTranslation 1.0

Pane {
    id: rootItm
    property string path : ""

    padding: 0
    topPadding: 5
    readonly property int labelWidth : width / 4
    readonly property int rowHeight : height > 0 ? height / 13 : 10
    property real pointSize: rowHeight / 2.8

    signal notification(string title, string msg);

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
        // Add models here once for all where all backend magic happens. Wanted
        // to use ListModel but that complained "cannot use script for property
        // value" due to Z.tr() - and handling of arrays is much simpler anyway...
        readonly property var modeModelBackend: ["MANUAL", "AUTOMATIC"]
        readonly property var modeModelDisplay: [Z.tr("Manual"), Z.tr("Automatic (DHCP)")]
        // plausibitity helper(s)
        function ipFieldsEnabled(modeIndex) {
            var ret = false
            if(modeIndex >= 0) {
                // we might need changes here in the future...
                ret = modeModelBackend[modeIndex] !== "AUTOMATIC"
            }
            return ret
        }
        onLoadComplete: {
            name.text = backend.conName;
            ipv4Mode.currentIndex = backend.modeModelBackend.indexOf(backend.ipv4Mode)
            ipv4.text = backend.ipv4;
            sub4.text = backend.ipv4Sub;
            ipv6Mode.currentIndex = backend.modeModelBackend.indexOf(backend.ipv6Mode)
            ipv6.text = backend.ipv6;
            sub6.text = backend.ipv6Sub;
            var index = backend.device !== "" ? devices.find(backend.device, Qt.MatchExactly) : 0
            devices.currentIndex = index;
            backend.device = devices.model[devices.currentIndex]
        }
    }
    VisualItemModel {
        id: clientModel
        Label {
            id: header
            anchors.left: parent.left
            anchors.right: parent.right
            height: rowHeight
            font.pointSize: pointSize * 1.25
            font.bold: true
            horizontalAlignment: Label.AlignHCenter
            text: Z.tr("Ethernet Connection Settings")
        }
        //--------------------------
        // Connection name area
        ZLineEdit {
            id: name
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            height: rowHeight
            pointSize: rootItm.pointSize
            description.text: Z.tr("Connection name:")
            description.width: labelWidth
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
            text: Z.tr("IPv4")
            anchors.left: parent.left
            anchors.right: parent.right
            height: rowHeight
            font.pointSize: pointSize
            font.bold: true
            verticalAlignment: Label.AlignBottom
        }
        RowLayout {
            id: ipv4ModeL
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: ZCC.standardTextHorizMargin // same as ZLineEdit
            Label {
                id: ipv4ModeLabel
                text: Z.tr("Mode:")
                Layout.preferredWidth: labelWidth - ZCC.standardTextHorizMargin
                font.pointSize: pointSize
            }
            ComboBox {
                id: ipv4Mode
                height: rowHeight
                Layout.fillWidth: true
                font.pointSize: pointSize
                model: backend.modeModelDisplay
                onCurrentIndexChanged: {
                    backend.ipv4Mode = backend.modeModelBackend[currentIndex]
                }
            }
        }

        // Explanation: At the time of writing QML shows odd behavior on focus
        // sequence:
        // enter ipv4: ipv4 activeFocus=true
        // enter sub4: sub4 activeFocus=true and THEN!! ipv4 activeFocus=true
        property int hackFieldFocusCount: 0
        ZLineEdit {
            id: ipv4
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            description.text: Z.tr("IP:")
            description.width: labelWidth
            height: rowHeight
            pointSize: rootItm.pointSize
            validator: RegExpValidator { regExp: /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/}
            enabled: backend.ipFieldsEnabled(ipv4Mode.currentIndex)
            // overrides
            function doApplyInput(newText) {
                backend.ipv4 = newText;
                return true
            }
            function activeFocusChange(actFocus) {
                baseActiveFocusChange(actFocus)
                // hack: force virtual keyboard numeric with decimal point
                textField.inputMethodHints = Qt.ImhFormattedNumbersOnly
                if(actFocus) {
                    clientModel.hackFieldFocusCount++ // see coment at definition
                    VirtualKeyboardSettings.locale = "en_GB"
                }
                else {
                    clientModel.hackFieldFocusCount--
                    if(clientModel.hackFieldFocusCount === 0)
                        VirtualKeyboardSettings.locale = ZLocale.localeName
                }
            }
        }
        ZLineEdit {
            id: sub4
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            description.text: Z.tr("Subnetmask:")
            description.width: labelWidth
            height: rowHeight
            pointSize: rootItm.pointSize
            validator: RegExpValidator { regExp: /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/}
            enabled: backend.ipFieldsEnabled(ipv4Mode.currentIndex)
            // overrides
            function doApplyInput(newText) {
                backend.ipv4Sub = newText;
                return true
            }
            function activeFocusChange(actFocus) {
                baseActiveFocusChange(actFocus)
                // hack: force virtual keyboard numeric with decimal point
                textField.inputMethodHints = Qt.ImhFormattedNumbersOnly
                if(actFocus) {
                    clientModel.hackFieldFocusCount++ // see coment at definition
                    VirtualKeyboardSettings.locale = "en_GB"
                }
                else {
                    clientModel.hackFieldFocusCount--
                    if(clientModel.hackFieldFocusCount === 0)
                        VirtualKeyboardSettings.locale = ZLocale.localeName
                }
            }
        }

        //--------------------------
        // IPv6 area
        Label {
            id: ipv6header
            text: Z.tr("IPv6")
            anchors.left: parent.left
            anchors.right: parent.right
            height: rowHeight
            font.pointSize: pointSize
            font.bold: true
            verticalAlignment: Label.AlignBottom
        }
        RowLayout {
            id: ipv6ModeL
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: ZCC.standardTextHorizMargin // same as ZLineEdit
            Label {
                id: ipv6ModeLabel
                text: Z.tr("Mode:")
                Layout.preferredWidth: labelWidth - ZCC.standardTextHorizMargin
                font.pointSize: pointSize
            }
            ComboBox {
                id: ipv6Mode
                height: rowHeight
                Layout.fillWidth: true
                font.pointSize: pointSize
                model: backend.modeModelDisplay
                onCurrentIndexChanged: {
                    backend.ipv6Mode = backend.modeModelBackend[currentIndex]
                }
            }
        }
        ZLineEdit {
            id: ipv6
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            description.text: Z.tr("IP:")
            description.width: labelWidth
            height: rowHeight
            pointSize: rootItm.pointSize
            validator: RegExpValidator { regExp: /([a-f0-9:]+:+)+[a-f0-9]+/}
            enabled: backend.ipFieldsEnabled(ipv6Mode.currentIndex)
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
            description.text: Z.tr("Subnetmask:")
            description.width: labelWidth
            height: rowHeight
            pointSize: rootItm.pointSize
            // TODO: This looks like a copy & paste from IPv4
            validator: RegExpValidator { regExp: /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/}
            enabled: backend.ipFieldsEnabled(ipv6Mode.currentIndex)
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
        anchors.bottom: okCancelButtonRow.top
        anchors.left: parent.left
        anchors.right: parent.right
        model: clientModel
        clip: true
    }
    //--------------------------
    // OK / Cancel buttons
    RowLayout {
        id: okCancelButtonRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        Item {
            Layout.fillWidth: true
        }
        Button {
            id: cancelButton
            text: Z.tr("Cancel")
            font.pointSize: pointSize
            onClicked: {
                backend.discard();
                rootItm.visible = false
            }
        }
        Button {
            id: okButton
            text: Z.tr("OK")
            font.pointSize: pointSize
            Layout.preferredWidth: cancelButton.width
            onClicked: {
                var good = true;
                var errorField;

                if(!ipv6.acceptableInput && ipv6.enabled) {
                    good = false;
                    errorField = Z.tr("IPV6 IP")
                } else if(!sub6.acceptableInput && sub6.enabled) {
                    good = false;
                    errorField = Z.tr("IPV6 Subnetmask")
                } else if(!ipv4.acceptableInput &&ipv4.enabled) {
                    good = false;
                    errorField = Z.tr("IPV4 IP")
                } else if(!sub4.acceptableInput && sub4.enabled) {
                    good = false;
                    errorField = Z.tr("IPV4 Subnetmask")
                } else if(!name.acceptableInput){
                    good = false;
                    errorField = Z.tr("Connection name")
                }
                if(good) {
                    backend.save();
                    rootItm.visible = false
                } else {
                    notification(Z.tr("Network settings"), Z.tr("invalid settings in field: ") + errorField)
                }
            }
        }
    }
}
