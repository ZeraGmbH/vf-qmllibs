import QtQuick 2.14
import QtQuick.Controls 2.14
import ZeraComponents 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "Journal viewer"

    width: 1280
    height: 1024

    ZJournalView {
        anchors.fill: parent
        Component.onCompleted: model.start()
    }
}
