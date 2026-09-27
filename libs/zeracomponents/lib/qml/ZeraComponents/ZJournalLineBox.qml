import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14

Rectangle {
    implicitWidth: height * 0.7 * (timestamp + " " + message).length
    color: {
        if (type === 3) // error
            return Material.color(Material.Red)
        if (type === 4) // warning
            return Qt.darker(Material.color(Material.Yellow), 2.75)
        if (type === 5) // debug
            return Qt.darker(Material.color(Material.Grey), 2.75)
        if (type === 6) // audit
            return Qt.darker(Material.color(Material.Blue), 2.75)
        return Qt.darker(Material.color(Material.Grey), 2.5)
    }
}