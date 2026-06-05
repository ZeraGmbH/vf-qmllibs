import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import ZeraTranslation 1.0
import anmsettings 1.0

Pane {
    id: rootItm
    Label{
        id: header
        text: Z.tr("Connection Information")
        font.pixelSize: rootItm.width/40
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ListView{
        id: list
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 15
        clip: true
        model: InfoInterface { }
        property int fontSize: rootItm.width/50

        delegate: Grid {
            columns: 2
            Label {
                text: device
                font.bold: true
                font.underline: true
                anchors.bottomMargin: 3
                font.pixelSize: list.fontSize
            }
            Item {
                id: spacer
                width: 1
                height: 1
            }

            Label {
                text: "IPv4: "
                font.pixelSize: list.fontSize
            }
            Label {
                text: ipv4
                font.pixelSize: list.fontSize
            }

            Label {
                text: Z.tr("Netmask:") + " "
                font.pixelSize: list.fontSize
            }
            Label {
                text: subnetmask
                font.pixelSize: list.fontSize
            }

            Label {
                text: "IPv6: "
                font.pixelSize: list.fontSize
            }
            Label {
                text: ipv6
                font.pixelSize: list.fontSize
            }
        }
    }
}
