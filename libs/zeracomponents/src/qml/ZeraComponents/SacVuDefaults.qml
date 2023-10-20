import QtQuick 2.14

Item {
    property real nominal
    property real overshootFactor
    property real actual
    property bool horizontal: false
    property bool mirror: false
    property bool softOvershoot: false

    property real relIndicatorLen: 0.95
    property real relIndicatorWidth: 0.02

    property color vuBackColor: "dimgray"
    property color vuNominalColor: "lawngreen"
    property color vuOvershootColor1: "yellow"
    property color vuOvershootColor2: "red"
    property color vuOvershootIndicatorColor: softOvershoot ? vuNominalColor : vuOvershootColor1 // to hide set "transparent"
}

