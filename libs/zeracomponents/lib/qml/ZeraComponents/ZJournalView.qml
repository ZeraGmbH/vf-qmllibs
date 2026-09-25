import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import ZJournalModel 1.0

ListView {
    id: root
    property real rowHeight: 16
    property int scrollbarWidth: 8

    clip: true

    ScrollBar.vertical: ScrollBar {
        anchors.right: parent.right
        width: scrollbarWidth
        orientation: Qt.Vertical
        policy: ScrollBar.AlwaysOn
    }
    model: ZJournalModel {}
    delegate: Label {
        width: root.width - scrollbarWidth
        height: rowHeight
        clip: true

        text: {
            if (timestamp === "")
                return message
            return timestamp + " " + message
        }

        font.family: "monospace"
        font.pointSize: rowHeight*0.6

        color: {
            if (type === 3) // error
                return Material.color(Material.Red)
            if (type === 4) // warning
                return Material.color(Material.Yellow)
            if (type === 5) // debug
                return Material.color(Material.Grey)
            if (type === 6) // audit
                return Material.color(Material.Blue)
            return Material.foreground
        }
        font.bold: type == 2
    }
}

