import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import ZeraTranslation 1.0

Popup {
    property string messageStr
    signal sigDeleteConfirmed()

    id: deleteConfirmationPopup
    parent: Overlay.overlay
    anchors.centerIn: parent
    modal: true
    property real rowHeight: parent ? Math.max(parent.height / 25, 10) : 10
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
            text: messageStr
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

