import QtQuick 2.9
import QtQuick.Controls 2.14
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.14
import ChartItemQml 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "ChartItem test"
    width: 800
    height: 400

    ChartItemQml {
        anchors.fill: parent
    }
}

