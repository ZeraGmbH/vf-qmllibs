import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import ZJournalModel 1.0

Item {
    id: root
    property real rowHeight: 16
    property real verticalScrollbarWidth: 0.1 // relative 0..1
    property int horizontalScrollbarHeight: 8
    readonly property QtObject model: ZJournalModel {}
    function positionViewAtEnd() {
        flickableContent.contentY = Math.max(0, flickableContent.contentHeight - flickableContent.height)
    }


    readonly property real absVerticalScrollbarWidth: root.width * verticalScrollbarWidth
    Flickable {
        id: flickableContent
        anchors { fill: parent; rightMargin: absVerticalScrollbarWidth; bottomMargin: horizontalScrollbarHeight}
        contentHeight: contentRows.implicitHeight
        contentWidth: contentRows.implicitWidth
        readonly property real lineHeight: contentHeight / root.model.rowCount() // pixel
        readonly property real firstVisibleLine: contentY / lineHeight
        readonly property real lastVisibleLine: firstVisibleLine + height / lineHeight
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
        width: absVerticalScrollbarWidth
        height: root.height
        orientation: Qt.Vertical
        policy: ScrollBar.AlwaysOn
        readonly property int lineHeight: 1 // pixel
        background: Flickable {
            id: flickableScrollBackgound
            anchors { fill: parent; leftMargin: 3; bottomMargin: root.height * 0.0015; topMargin: root.height * 0.0015}
            contentWidth: scrollBackgroundContents.implicitWidth
            contentHeight: scrollBackgroundContents.implicitHeight
            contentX: (contentWidth-width) * horizontalScrollbar.position / (1-horizontalScrollbar.size)
            contentY: (contentHeight-height) * verticalScrollbar.position / (1-verticalScrollbar.size)
            interactive: false
            clip: true

            Column {
                id: scrollBackgroundContents
                Repeater {
                    model: root.model
                    delegate: ZJournalLineBox { height: verticalScrollbar.lineHeight }
                }
            }
        }
        contentItem: Item { // ScrollBar adapts height / we set height -> 'hide' rectangle in item
            id: scrollHandle
            Rectangle {
                id: scrollRectangle
                width: absVerticalScrollbarWidth
                height: (flickableContent.lastVisibleLine - flickableContent.firstVisibleLine) * verticalScrollbar.lineHeight
                color: mouseArea.pressed ? "#ffffff" : "#80ffffff"
                opacity: mouseArea.hovered ? 0.6 : 0.4
                border.color: "#ffffff"
                border.width: 2
                y: (scrollHandle.height - height) * verticalScrollbar.position / (1-verticalScrollbar.size) // rectangle moves around in contentItem
            }
        }
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            function calcContentY(mouse) {
                let previewY = mouse.y + flickableScrollBackgound.contentY
                let targetLine = previewY / verticalScrollbar.lineHeight
                let targetY = (targetLine * flickableContent.lineHeight) - (flickableContent.height / 2)
                let minY = 0
                let maxY = flickableContent.contentHeight - flickableContent.height
                return Math.max(minY, Math.min(maxY, targetY))
            }
            onPressed: (mouse) => flickableContent.contentY = calcContentY(mouse)
            onPositionChanged: (mouse) => {
                if (pressed)
                    flickableContent.contentY = calcContentY(mouse)
            }
        }
    }
    ScrollBar {
        id: horizontalScrollbar
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: root.width - absVerticalScrollbarWidth
        height: horizontalScrollbarHeight
        orientation: Qt.Horizontal
        policy: ScrollBar.AlwaysOn
    }
}