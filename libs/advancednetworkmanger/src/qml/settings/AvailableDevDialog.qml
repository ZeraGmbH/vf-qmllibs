import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import anmsettings 1.0
import ZeraTranslation 1.0

Dialog {
    id: rootItm
    title: Z.tr("Device Binding")
    property var devices

    signal okPressed(string retDevice)

    RowLayout{
        width: parent.width
        Label{
            id: devLabel
            text: Z.tr("Devices:")
        }

        ComboBox{
            id: devList
            Layout.fillWidth: true
            model: devices
        }
    }

    standardButtons: Dialog.Ok | Dialog.Cancel

    onAccepted: {
        okPressed(devList.currentText)
    }

}


