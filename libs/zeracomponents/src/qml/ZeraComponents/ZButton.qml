import QtQuick 2.0
import QtQuick.Controls 2.0

Button {
    id: root

    // Button has special ideas - force our margins
    background.anchors.fill: root
    background.anchors.topMargin: 0
    background.anchors.bottomMargin: 0
    background.anchors.rightMargin: 0
}
