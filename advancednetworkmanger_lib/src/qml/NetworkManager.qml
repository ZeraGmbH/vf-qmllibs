import QtQuick 2.0
import QtQuick.Controls 2.12
import SortFilterProxyModel 0.2
import QtQuick.Layouts 1.12

import anmsettings 1.0

import "qrc:/src/qml/settings"
import "qrc:/src/qml/tree"
import "qrc:/src/qml/FontAwesome.js" as FA





Pane{
    id: rootItm
    padding: 0

    signal notification(string title,string msg);


    ConnectionTree{
        id: tree
        anchors.fill: parent
    }

}




