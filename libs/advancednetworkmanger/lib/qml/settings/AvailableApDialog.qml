import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import anmsettings 1.0
import ZeraTranslation 1.0

Dialog {
    id: rootItm
    title: Z.tr("Wifi SSID")

    signal okPressed(string retSsid)

    NetworkmanagerAbstraction{
        id: backend
    }
    RowLayout{
        width: parent.width
        Label{
            id: pwLabel
            text: Z.tr("Networks:")
        }
        ComboBox{
            id: ssidList
            Layout.fillWidth: true
            model: backend.aps
        }
    }
    standardButtons: Dialog.Ok | Dialog.Cancel
    onAccepted: {
        okPressed(ssidList.currentText)
    }

}


