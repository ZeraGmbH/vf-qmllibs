import QtQuick 2.0
import QtQuick.Controls 2.0

Popup {
    id: popup
    modal: false
    focus: false
    anchors.centerIn: parent
    property alias text: txt.text
    property alias title: tit.text
    closePolicy: Popup.NoAutoClose
    verticalPadding: 2
    horizontalPadding: 2
    background: Rectangle {
        color: "grey"
        radius: 5
        border.color: "black"
    }

    contentItem: Item {
        id: con
        Column{
            id: col
            Label {
                id: tit
                padding: 1
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                width: popup.width
                font.pixelSize: txt.font.pixelSize+4
                wrapMode: Text.Wrap
                font.bold: true
                color: "white"
            }
            Label {
                id: txt
                padding: 2
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                width: popup.width
                wrapMode: Text.Wrap
                color: "white"
            }
        }
    }
}
