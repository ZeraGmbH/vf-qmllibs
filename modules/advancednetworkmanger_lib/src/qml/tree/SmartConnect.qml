import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import anmsettings 1.0
import ZeraFa 1.0

Dialog {
    id: rootItm
    title: "WIFI PASSWORD"
    property string device: ""
    property string path: ""
    closePolicy: Popup.NoAutoClose

    function init(ssid,device,path){
        backend.create();
        rootItm.device=device;
        rootItm.path = path;
        backend.conName = ssid;
        backend.ssid = ssid;
        backend.mode = "CLIENT";
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
                text: "Password: "
            }
            TextField {
                id: pw
                echoMode: TextInput.Password
                Layout.fillWidth: true
                validator: RegExpValidator{ regExp: /.{8,}/}
                Material.accent: {
                    if(!acceptableInput) {
                        return Material.Red;
                    } else {
                        return Material.Green;
                    }
                }
                //focus: true
                Keys.onEscapePressed: {
                  focus = false
                }
                onEditingFinished: {
                    backend.password=text;
                }
            }
            Button{
                id: pwvisible
                font.family: FA.old
                text: FA.icon(FA.fa_eye_slash,null)
                font.pixelSize: rootItm.fontPixelSize
                background: Rectangle{
                    color: "transparent"
                }
                onPressed: {
                    pw.echoMode = TextInput.Normal
                    pwvisible.text= FA.icon(FA.fa_eye,null)
                }
                onReleased: {
                    pw.echoMode = TextInput.Password
                    pwvisible.text= FA.icon(FA.fa_eye_slash,null)
                }
            }
        }
        RowLayout {
            id: devInput
            width: parent.width
            Label {
                id: devLabel
                text: "Device: "
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
    onDiscarded: {
        backend.discard();
    }
    standardButtons: Dialog.Ok | Dialog.Cancel
}
