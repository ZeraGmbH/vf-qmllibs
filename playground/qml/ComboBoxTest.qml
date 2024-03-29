import QtQuick 2.9
import QtQuick.Controls 2.14
import Qt.labs.platform 1.0
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import ZeraComponents 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "ZComboBox test"
    width: 800
    height: 800

    readonly property real lineHeight: height * 0.05
    Rectangle {
        id: controls
        anchors.top: parent.top
        height: lineHeight
        anchors.left: parent.left
        anchors.right: parent.right
        color: Material.backgroundColor
        border.color: Material.dividerColor
        border.width: 1
        RowLayout {
            id: controlRow1
            CheckBox {
                id: optApplicationBorder
                text: "Application border"
            }

            Label {
                text: "contentMaxRows:"
            }
            SpinBox {
                id: optContentMaxRows
                from: 0
                to: testContent.length
                value: to
            }
            CheckBox {
                text: "popupKeepHorizontalSize"
                id: optPopupKeepHorizontalSize
            }
        }
    }

    readonly property int xyCount: 3
    readonly property real relWidth: 1
    readonly property real relHeight: 1 / testContent.length
    readonly property var testContent: ["First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "NineTh"]
    Column {
        id: comboCollectionDisplay
        anchors.top: controls.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        Repeater {
            id: rows
            model: xyCount
            delegate: Row {
                id: rowDelegate
                readonly property int currIndex: index
                width: parent.width
                height: parent.height / rows.count
                Repeater {
                    id: columns
                    model: xyCount
                    delegate: Rectangle {
                        id: columnDelegate
                        readonly property int currIndex: index
                        width: parent.width / columns.count
                        height: parent.height
                        color: Material.backgroundColor
                        border.color: Material.dividerColor
                        border.width: 1
                        Rectangle {
                            width: parent.width * relWidth
                            x: {
                                let ret = 0 // default: left
                                if(columnDelegate.currIndex === columns.count-1) // right
                                    ret = columnDelegate.width - width
                                else if(columnDelegate.currIndex != 0) // middle
                                    ret = columnDelegate.width/2 - width/2
                                return ret
                            }
                            height: parent.height * relHeight
                            y: {
                                let ret = 0 // default: top
                                if(rowDelegate.currIndex === rows.count-1) // bottom
                                    ret = rowDelegate.height - height
                                else if(rowDelegate.currIndex != 0) // middle
                                    ret = rowDelegate.height/2 - height/2
                                return ret
                            }
                            color: Material.backgroundColor
                            /*border.color: Material.dividerColor
                            border.width: 1*/

                            ZComboBox {
                                anchors.fill: parent
                                popupBorderItem: optApplicationBorder.checked ? ApplicationWindow.overlay : comboCollectionDisplay
                                contentMaxRows: optContentMaxRows.value
                                popupKeepHorizontalSize: optPopupKeepHorizontalSize.checked
                                arrayMode: true
                                model: testContent
                            }
                        }
                    }
                }
            }
        }
    }

    // Test cases
    // one element centered 1 / 3 elements
    // 8 at frame
    //
    // variations
    // multi column
    // header
}
