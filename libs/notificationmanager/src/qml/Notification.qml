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
        anchors.fill: parent
        implicitHeight: tit.implicitHeight+txt.implicitHeight+5
        MouseArea {
            anchors.fill: parent
            onClicked: {
                popup.close()
            }
        }
        Column{
            id: col
        Label{
            padding: 2
            width: popup.width
            id: tit
            font.pixelSize: txt.font.pixelSize+4
            wrapMode: Text.Wrap
            font.bold: true

        }
        Label {
            padding: 2
            width: popup.width
            id: txt
            wrapMode: Text.Wrap
        }
        }
    }
}
