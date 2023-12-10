import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import anmsettings 1.0
import ZeraFa 1.0
import "../settings"
import "../tree"

Pane{
    id: rootItm
    padding: 0

    ConnectionTree{
        id: tree
        anchors.fill: parent
    }
}
