import QtQuick 2.14
import QtQuick.Controls 2.14
import "../tree"

Pane{
    id: rootItm
    padding: 0

    ConnectionTree{
        id: tree
        anchors.fill: parent
    }
}
