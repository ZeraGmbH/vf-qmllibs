import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4

import anmsettings 1.0


Pane {
id: rootItm
    Label{
        id: header
        text: "Connection Information"
        font.pixelSize: 18
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
        model: InfoInterface{

        }

        delegate: Grid{
                columns: 2
            Label {
                text: device
                font.bold: true
                font.underline: true
            }

            Item {
                id: spacer
                width: 1
                height: 1
            }


            Label {
                text: "ipv4: "

            }

            Label {
                text: ipv4

            }

            Label {
                text: "subnetmask: "

            }

            Label {
                text: subnetmask

            }

            Label {
                text: "ipv6: "

            }

            Label {
                text: ipv6

            }
        }
    }






}
