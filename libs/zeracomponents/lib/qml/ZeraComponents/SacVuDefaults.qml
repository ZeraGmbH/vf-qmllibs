import QtQuick 2.14
import ZeraThemeConfig 1.0

Item {
    property real nominal
    property real overshootFactor
    property real actual
    property bool horizontal: false
    property bool mirror: false
    property bool softOvershoot: false

    property real relIndicatorLen: 0.95
    property real relIndicatorWidth: 0.02
    property real vuStartRadius: 0//vuEndRadius * 0.2
    property real vuEndRadius: horizontal ? height/2 : width/2

    property color vuBackColor: ZTC.dividerColor
    property color vuNominalColor: "lawngreen"
    property color vuOvershootColor1: "yellow"
    property color vuOvershootColor2: "red"
    property color vuOvershootIndicatorColor: softOvershoot ? vuNominalColor : vuOvershootColor1 // to hide set "transparent"
}

