import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import ZJournalModel 1.0

ScrollView {
    id: root
    property alias model: logView.model

    anchors.fill: parent
    ScrollBar.vertical.policy: ScrollBar.AsNeeded
    ScrollBar.horizontal.policy: ScrollBar.AsNeeded

    ListView {
        id: logView
        clip: true

        model: ZJournalModel {}
        delegate: Label {
            width: Math.max(implicitWidth, logView.width)
            text: {
                let txt
                if (timestamp !== "")
                    txt = timestamp + " "
                txt += message
                return txt
            }

            font.family: "monospace"
            font.pixelSize: 13

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
}

