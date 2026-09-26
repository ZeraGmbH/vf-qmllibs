import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import ZJournalModel 1.0

Item {
    id: root
    property real rowHeight: 16
    property int scrollbarWidth: 80
    property int scrollbarHeight: 8
    readonly property QtObject model: ZJournalModel {}
    function positionViewAtEnd() {
        flickable.contentY = Math.max(0, flickable.contentHeight - flickable.height)
    }

    Flickable {
        id: flickable
        anchors.fill: parent
        anchors.rightMargin: scrollbarWidth
        anchors.bottomMargin: scrollbarHeight
        contentHeight: contentRows.implicitHeight
        contentWidth: contentRows.implicitWidth
        clip: true
        Column {
            id: contentRows
            clip: true
            Repeater {
                model: root.model
                delegate: ZJournalLine { height: rowHeight }
            }
        }
        ScrollBar.vertical: verticalScrollbar
        ScrollBar.horizontal: horizontalScrollbar
    }
    ScrollBar {
        id: verticalScrollbar
        anchors.right: parent.right
        width: scrollbarWidth
        height: root.height
        orientation: Qt.Vertical
        policy: ScrollBar.AlwaysOn
        background: ShaderEffectSource {
            anchors.fill: parent
            sourceItem: contentRows
        }
    }
    ScrollBar {
        id: horizontalScrollbar
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: root.width - scrollbarWidth
        height: scrollbarHeight
        orientation: Qt.Horizontal
        policy: ScrollBar.AlwaysOn
    }
}