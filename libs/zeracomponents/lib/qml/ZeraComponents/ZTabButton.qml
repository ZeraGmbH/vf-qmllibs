import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.14
import QtQuick.Controls.Material.impl 2.14
import QtQuick.Controls.impl 2.14

TabButton {
    id: root

    // stolen from qtquickcontrols2 / src/imports/controls/material/TabButton.qml
    contentItem: IconLabel {
        spacing: root.spacing
        mirrored: root.mirrored
        display: root.display

        icon: root.icon
        text: root.text
        font: root.font
        color: !root.enabled ? root.Material.hintTextColor : root.down || root.checked ? root.Material.accentColor : root.Material.foreground
        // get rid of annoying / over enthusiastic elide
        Component.onCompleted: {
            if (children.length > 0)
                children[0].elide = Text.ElideNone
        }
    }
}
