import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.11
import QtQuick.Controls.Material 2.12
import anmsettings 1.0
import ZeraFa 1.0
import ZeraComponents 1.0
import ZeraComponentsConfig 1.0
import ZeraTranslation 1.0
import "../components"

Pane {
    id: rootItm
    property string path : ""
    property bool hotspot: true

    anchors.fill: parent
    padding: 0
    topPadding: 10
    readonly property int rowHeight : height > 0.0 ? height / 10 : 10
    property real pointSize: rowHeight / 2.8
    property int labelWidth : rootItm.width / 3

    signal notification(string title, string msg);

    function init() {
        if(path === "") {
            backend.create();
        } else {
            backend.load(path);
        }
    }
    function autoMoveFocusToNext() {
        if(!ssid.text.focus && ssid.text === "") {
            ssid.textField.focus = true
        }
        else if(!pw.text.focus && pw.text === "") {
            pw.textField.focus = true
        }

    }

    NetworkmanagerAbstraction {
        id: generalbackend
    }
    WirelessConnectionSettingsInterface {
        id: backend
        onLoadComplete: {
            // do not change the order mode sets some values to defaults.
            // incase this is a existing connection we do not want those defaults
            // but the actual set value.
            if(path === "") {
                if(hotspot) {
                    backend.mode = "HOTSPOT"
                    name.text = backend.getNextHotspotName(Z.tr("Hotspot"));
                    ssid.text = backend.getHostName();
                    backend.ssid = ssid.text
                    pw.textField.forceActiveFocus()
                }
                else {
                    backend.mode = "CLIENT"
                    name.text = backend.getNextHotspotName(Z.tr("Wifi"));
                    ssid.textField.forceActiveFocus()
                }
                backend.conName = name.text
            }
            else {
                name.text = backend.conName;
                ssid.text = backend.ssid;
            }
            ipv4.text = backend.ipv4
            pw.text = backend.password;
            device.text = backend.device;
            autoConCheckbox.checked = backend.autoconnect;
        }
    }
    ObjectModel {
        id: clientModel
        HackVKeyboardFocus {
            id: hackVkFocusHelper
        }

        Loader {
            id: header
            anchors.left: parent.left
            anchors.right: parent.right
            active: path !== ""
            sourceComponent: Label {
                font.pointSize: pointSize * 1.25
                font.bold: true
                horizontalAlignment: Label.AlignHCenter
                text: hotspot ? Z.tr("Hotspot Settings") : Z.tr("Wifi Settings")
            }
        }

        ZLineEdit {
            id: name
            anchors.left: parent.left
            width: parent.width - rowHeight
            height: rowHeight
            pointSize: rootItm.pointSize
            description.text: Z.tr("Connection name:")
            description.width: labelWidth
            validator: RegExpValidator{ regExp: /.{1,}/ }
            function doApplyInput(newText) {
                backend.conName = newText;
                return true
            }
            textField.onAccepted: {
                autoMoveFocusToNext()
            }
        }
        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: rowHeight
            // Just for the record: this remains enabled for hotpot AND CLIENT
            // -> we might want to create a client for a hidden SSID
            ZLineEdit {
                id: ssid
                anchors.left: parent.left
                anchors.right: ssidButton.left
                height: rowHeight
                pointSize: rootItm.pointSize
                description.text: Z.tr("SSID:")
                description.width: labelWidth
                validator: RegExpValidator{ regExp: /.{1,}/}
                function doApplyInput(newText) {
                    backend.ssid = newText;
                    return true
                }
                textField.onAccepted: {
                    autoMoveFocusToNext()
                }
            }
            Button {
                id: ssidButton
                anchors.right: parent.right
                font.family: FA.old
                font.pointSize: pointSize
                width: rowHeight
                height: rowHeight
                text: FA.fa_search_plus
                visible: !hotspot
                onClicked: {
                    aApDialog.visible = true;
                }
            }
        }
        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: rowHeight
            ZLineEdit {
                id: pw
                textField.echoMode: TextInput.Password
                anchors.left: parent.left
                anchors.right: pwvisible.left
                height: rowHeight
                pointSize: rootItm.pointSize
                description.text: Z.tr("Password:")
                description.width: labelWidth
                validator: RegExpValidator{ regExp: /.{8,}/}
                function doApplyInput(newText) {
                    backend.password = newText;
                    return true
                }
            }
            Button {
                id: pwvisible
                anchors.right: parent.right
                font.family: FA.old
                font.pointSize: pointSize
                width: rowHeight
                height: rowHeight
                text: FA.fa_eye_slash
                onPressed: {
                    pw.textField.echoMode = TextInput.Normal
                    pwvisible.text= FA.fa_eye
                }
                onReleased: {
                    pw.textField.echoMode = TextInput.Password
                    pwvisible.text= FA.fa_eye_slash
                }
            }
        }
        ZLineEdit {
            id: ipv4
            anchors.left: parent.left
            width: rootItm.width - rowHeight
            description.text: Z.tr("IP:")
            description.width: labelWidth
            height: rowHeight
            pointSize: rootItm.pointSize
            validator: RegExpValidator { regExp: /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/}
            visible: hotspot
            // overrides
            function doApplyInput(newText) {
                backend.ipv4 = newText;
                return true
            }
            function activeFocusChange(actFocus) {
                baseActiveFocusChange(actFocus)
                // hack: force virtual keyboard numeric with decimal point
                textField.inputMethodHints = Qt.ImhFormattedNumbersOnly
                hackVkFocusHelper.hackVKeyboardSettings(actFocus)
            }
        }
        RowLayout{
            width: rootItm.width
            height: rootItm.rowHeight
            Label {
                id: autoconLabel
                font.pointSize: pointSize
                text: Z.tr("Autoconnect:")
                Layout.preferredWidth: labelWidth - ZCC.standardTextHorizMargin
            }
            ZCheckBox{
                id: autoConCheckbox
                Layout.fillHeight: true
                display: AbstractButton.IconOnly
                Layout.alignment: Qt.AlignRight
                onCheckedChanged: {
                    backend.autoconnect=checked;
                }
            }
        }
    }
    ListView {
        id: list
        anchors.top: parent.top
        anchors.bottom: okCancelButtonRow.top
        anchors.left: parent.left
        anchors.right: parent.right
        model: clientModel
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
        Button{
            id: cancelButton
            text: Z.tr("Cancel")
            font.pointSize: pointSize
            onClicked: {
                backend.discard();
                rootItm.visible = false
            }
            width: implicitContentWidth
            height: implicitContentHeight
        }
        Button {
            id: okButton
            text: Z.tr("OK")
            font.pointSize: pointSize
            Layout.preferredWidth: cancelButton.width
            height: implicitContentHeight
            onClicked: {
                var good = true;
                var errorField = "";
                if(!name.acceptableInput) {
                    good = false;
                    errorField = Z.tr("Connection name")
                } else if(!ssid.acceptableInput) {
                    good = false;
                    errorField = Z.tr("SSID")
                } else if(!pw.acceptableInput) {
                    good = false;
                    errorField = Z.tr("Password")
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
    //--------------------------
    // Dialogs
    AvailableApDialog {
        id: aApDialog
        width: parent.width*0.9
        parent: Overlay.overlay
        x: 0
        y: 0
        onOkPressed: {
            ssid.text = retSsid;
            backend.ssid = retSsid;
        }
    }
    AvailableDevDialog {
        id: aDevDialog
        width: parent.width*0.9
        devices: backend.devices;
        parent: Overlay.overlay
        x: 0
        y: 0
        onOkPressed: {
            device.text = retDevice;
            backend.device = retDevice;
        }
    }
}
