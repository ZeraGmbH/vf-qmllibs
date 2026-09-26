import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14

Label {
    clip: true

    text: {
        if (timestamp === "")
            return message
        return timestamp + " " + message
    }
    textFormat: Text.PlainText

    font.family: "monospace"
    font.pointSize: height*0.6

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