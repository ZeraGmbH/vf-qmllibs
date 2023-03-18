import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import anmsettings 1.0
import ZeraTranslation 1.0

Dialog {
    id: rootItm
    title: Z.tr("Select device")

    property string name: ""
    property bool stored: true
    property int type: 0
    signal devChosen(string dev,string name, bool stored);

    function init(name,stored,type) {
        rootItm.name = name;
        rootItm.stored = stored;
        deviceList.model = backend.getDevices(type);
    }
    NetworkmanagerAbstraction{
        id: backend
    }
    RowLayout {
        width: parent.width
        Label {
            id: deviceLabel
            text: "Device "
        }
        ComboBox {
            id: deviceList
            Layout.fillWidth: true
        }
    }
    standardButtons: Dialog.Ok | Dialog.Cancel
    onAccepted: {
        var dev=backend.getDevicePath(deviceList.model[deviceList.currentIndex]);
        devChosen(dev,rootItm.name,rootItm.stored);
   }
}




