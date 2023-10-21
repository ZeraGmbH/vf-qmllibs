import QtQuick 2.14
import QtQuick.Controls 2.14

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "Simple and cheap (Sac) VU"
    width: 750
    height: 300

    TabBar {
        id: tabBar
        width: parent.width
        TabButton { text: "Unsigned" }
        TabButton { text: "Signed" }
    }
    SwipeView {
        anchors.top: tabBar.bottom
        anchors.bottom: parent.bottom
        id: swipeView
        width: parent.width
        currentIndex: tabBar.currentIndex
        SacVuTestViewUnsigned {}
        SacVuTestViewSigned {}
    }
}
