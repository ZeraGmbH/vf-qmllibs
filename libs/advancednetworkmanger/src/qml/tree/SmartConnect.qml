import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls.Material 2.14
import ZeraTranslation 1.0
import anmsettings 1.0
import "../components"
import ZeraFa 1.0

Dialog {
    id: rootItm
    title: Z.tr("Wifi password: ")+backend.ssid
    Binding {
        target: header
        property: 'font.pixelSize'
        value: rootItm.width/55
    }

    font.pixelSize: width/50
    property string device: ""
    property string path: ""
    property bool newCon: true
    property ConnectionRowAdvanced rowObject
    closePolicy: Popup.NoAutoClose

    function init(ssid, device,path,newCon,rowObject) {
        rootItm.newCon=newCon;
        rootItm.rowObject=rowObject;
        if(newCon){
            backend.create();
            rootItm.device = device;
            rootItm.path = path;
            backend.conName = ssid;
            backend.ssid = ssid;
            backend.mode = "CLIENT";
        }else{
            rootItm.path = path;
            backend.load(rootItm.path)
            pw.text = backend.password
            rootItm.device = device;
            backend.conName = ssid;
            backend.ssid = ssid;
            backend.mode = "CLIENT";
        }

    }
    WirelessConnectionSettingsInterface{
        id: backend
    }
    Column {
        anchors.fill: parent
        RowLayout{
            id: pwInput
            width: parent.width
            Label {
                id: pwLabel
                text: Z.tr("Password:")
            }
            TextField {
                id: pw
                echoMode: pwvisible.active ? TextInput.Normal : TextInput.Password
                Layout.fillWidth: true
                validator: RegularExpressionValidator{ regularExpression: /.{8,}/}
                horizontalAlignment: Text.AlignRight
                Material.accent: {
                    if(!acceptableInput) {
                        return Material.Red;
                    } else {
                        return Material.Green;
                    }
                }
                //focus: true
                Keys.onEscapePressed: {
                    focus = false;
                }

                Keys.onReturnPressed: {
                    backend.password=text;
                    rootItm.accept();
                }

                onEditingFinished: {
                    backend.password=text;
                }
            }
            PasswordPreviewButton {
                id: pwvisible
            }
        }
        RowLayout {
            id: devInput
            width: parent.width
            visible: {
                if(backend.devices.length>1){
                    return true;
                }
                return false;
            }

            Label {
                id: devLabel
                text: Z.tr("Device:")
            }
            ComboBox {
                id: devBinding
                Layout.fillWidth: true
                model: backend.devices;
                onCurrentIndexChanged: {
                    rootItm.device=backend.getDevicePath(model[currentIndex]);
                }
            }
        }
    }
    onAccepted: {
        backend.saveAndActivate(rootItm.device,rootItm.path);
    }

    onRejected: {
        backend.discard();
        rowObject.cancelConnect();
    }

    standardButtons: Dialog.Ok | Dialog.Cancel
}
