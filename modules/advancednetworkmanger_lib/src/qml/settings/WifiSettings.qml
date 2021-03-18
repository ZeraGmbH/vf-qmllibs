import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.11
import QtQuick.Controls.Material 2.12
import SortFilterProxyModel 0.2
import anmsettings 1.0
import ZeraFa 1.0
import ZeraComponents 1.0
import ZeraComponentsConfig 1.0
import ZeraTranslation 1.0

Pane {
    id: rootItm
    padding: 0
    topPadding: 5
    property string path : ""

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
    WirelessConnectionSettingsInterface {
        id: backend
        // Add models here once for all where all backend magic happens. Wanted
        // to use ListModel but that complained "cannot use script for property
        // value" due to Z.tr() - and handling of arrays is much simpler anyway...
        readonly property var modeModelBackend:      ["CLIENT", "HOTSPOT"]
        readonly property var modeModelDisplay: Z.tr(["Client", "Hotspot"])
        // plausibitity helper(s)
        function ssidEditableOnly(modeIndex) {
            // For hotspot we should not select from list (we would open a
            // hotpot with same ssid as available in our network)
            var ret = false
            if(modeIndex >= 0) {
                ret = modeModelBackend[modeIndex] === "HOTSPOT"
            }
            return ret
        }
        onLoadComplete: {
            // do not change the order mode sets some values to defaults.
            // incase this is a existing connection we do not want those defaults
            // but the actual set value.
            name.text = backend.conName;
            ssid.text = backend.ssid;
            mode.currentIndex = backend.modeModelBackend.indexOf(backend.mode);
            pw.text = backend.password;
            device.text = backend.device;

            autoConCheckbox.checked = backend.autoconnect;
        }
    }
    ObjectModel {
        id: clientModel
        property int labelWidth : rootItm.width/4
        readonly property int rowHeight : rootItm.height/12
        property real pointSize: clientModel.rowHeight / 2.8 // reduce ZLineEdit default slightly
        Label {
            id: header
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 18
            font.bold: true
            horizontalAlignment: Label.AlignHCenter
            text: Z.tr("Wifi Connection Settings")
        }
        ZLineEdit {
            id: name
            anchors.left: parent.left
            width: parent.width - clientModel.rowHeight
            height: clientModel.rowHeight
            pointSize: clientModel.pointSize
            description.text: Z.tr("Connection name:")
            description.width: clientModel.labelWidth
            validator: RegExpValidator{ regExp: /.{3,}/ }
            function doApplyInput(newText) {
                backend.conName = newText;
                return true
            }
        }
        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: clientModel.rowHeight
            // Just for the record: this remains enabled for hotpot AND CLIENT
            // -> we might want to create a client for a hidden SSID
            ZLineEdit {
                id: ssid
                anchors.left: parent.left
                anchors.right: ssidButton.left
                height: clientModel.rowHeight
                pointSize: clientModel.pointSize
                description.text: Z.tr("SSID:")
                description.width: clientModel.labelWidth
                validator: RegExpValidator{ regExp: /.{1,}/}
                function doApplyInput(newText) {
                    backend.ssid = newText;
                    return true
                }
            }
            Button {
                id: ssidButton
                anchors.right: parent.right
                font.family: FA.old
                font.pointSize: clientModel.pointSize
                width: clientModel.rowHeight
                height: clientModel.rowHeight
                text: FA.fa_search_plus
                visible: !backend.ssidEditableOnly(mode.currentIndex)
                /*background: Rectangle{
                    color: "transparent"
                }*/
                onClicked: {
                    aApDialog.visible = true;
                }
            }
        }
        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: clientModel.rowHeight
            ZLineEdit {
                id: pw
                textField.echoMode: TextInput.Password
                anchors.left: parent.left
                anchors.right: pwvisible.left
                height: clientModel.rowHeight
                pointSize: clientModel.pointSize
                description.text: Z.tr("Password:")
                description.width: clientModel.labelWidth
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
                font.pointSize: clientModel.pointSize
                width: clientModel.rowHeight
                height: clientModel.rowHeight
                text: FA.fa_eye_slash
                /*background: Rectangle{
                    color: "transparent"
                }*/
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
        RowLayout {
            id: conMode
            anchors.left: parent.left
            width: parent.width// - clientModel.rowHeight - ZCC.standardTextHorizMargin
            Label {
                id: modeLabel
                font.pointSize: clientModel.pointSize
                text: Z.tr("Mode:")
                Layout.preferredWidth: clientModel.labelWidth - ZCC.standardTextHorizMargin
            }
            ComboBox{
                id: mode
                Layout.fillWidth: true
                font.pointSize: clientModel.pointSize
                model: backend.modeModelDisplay
                onCurrentIndexChanged: {
                    backend.mode = backend.modeModelBackend[currentIndex];
                    if(backend.mode === "HOTSPOT"){
                        if(ssid.text === ""){
                            ssid.text = backend.getHostName();
                            ssid.doApplyInput(ssid.text)
                        }
                        if(name.text === ""){
                            name.text = backend.getNextHotspotName(Z.tr("Hotspot"));
                            name.doApplyInput(name.text)
                        }
                        autoConCheckbox.checked=false;
                    }
                }
            }
        }

        RowLayout{
            width: parent.width
            height: parent.rowHeight
            Label {
                id: autoconLabel
                font.pointSize: clientModel.pointSize
                text: Z.tr("Autoconnect:")
                Layout.preferredWidth: clientModel.labelWidth - ZCC.standardTextHorizMargin
            }
            CheckBox{
                id: autoConCheckbox
                display: AbstractButton.IconOnly
                Layout.alignment: Qt.AlignRight
                onCheckedChanged: {
                    backend.autoconnect=checked;
                }
            }
        }
    }
    ListView{
        id: list
        anchors.top: parent.top
        anchors.bottom: okButton.top
        anchors.left: parent.left
        anchors.right: parent.right
        model: clientModel
    }
    //--------------------------
    // OK / Cancel buttons
    ZButton {
        id: okButton
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        height: clientModel.rowHeight
        width: cancelButton.width
        text: Z.tr("OK")
        onClicked: {
            var good=true;
            var errorField="";
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
    ZButton{
        id: cancelButton
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: clientModel.rowHeight
        text: Z.tr("Cancel")
        onClicked: {
            backend.discard();
            rootItm.visible = false
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









