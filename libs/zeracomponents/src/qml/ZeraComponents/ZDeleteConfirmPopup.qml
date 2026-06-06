import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import ZeraTranslation 1.0

Popup {
    // User question will be
    // "Delete <deleteTypeStr> <deleteInstanceStr>?"
    // e.g
    // deleteTypeStr: Z.tr("network connection")
    // deleteInstanceStr: "Hotspot 1"
    // => "Delete network connection <bold>'Hotspot 1'</bold>?"
    property string deleteTypeStr
    property string deleteInstanceStr
    signal sigDeleteConfirmed()

    id: deleteConfirmationPopup
    parent: Overlay.overlay
    anchors.centerIn: parent
    modal: true
    property real rowHeight: parent.height / 25
    property real pointSize: rowHeight * 0.8
    readonly property real pointSizeHeader: pointSize * 1.25

    ColumnLayout {
        Label { // header
            text: Z.tr("Confirmation")
            font.pointSize: pointSizeHeader
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }
        Item { Layout.preferredHeight: rowHeight/3 }
        Label {
            text: Z.tr("Delete %1 <b>'%2'</b>?").arg(deleteConfirmationPopup.deleteTypeStr).arg(deleteConfirmationPopup.deleteInstanceStr)
            Layout.fillWidth: true
            font.pointSize: pointSize
        }
        Item { Layout.preferredHeight: rowHeight/3 }
        RowLayout {
            Layout.fillWidth: true
            Item { Layout.fillWidth: true }
            ZButton {
                id: cancelButton
                text: Z.tr("Cancel")
                font.pointSize: pointSize
                onClicked: {
                    deleteConfirmationPopup.close()
                }
            }
            ZButton {
                id: deleteButton
                text: "<font color='red'>" + Z.tr("Delete") + "</font>"
                font.pointSize: pointSize
                Layout.preferredWidth: cancelButton.width
                onClicked: {
                    sigDeleteConfirmed()
                }
            }
        }
    }
}

