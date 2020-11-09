
import QtQuick 2.0
import QtQuick.Controls 2.0

Popup {
    id: popup
    modal: false
    focus: false
    property alias text: txt.text
    property alias title: tit.text
    closePolicy: Popup.NoAutoClose

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
