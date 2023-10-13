import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14

Item {
    id: root
    // external interface
    property real nominal
    property real overshootFactor
    property real actual
    property bool horizontal: false
    property bool mirror: false
    property bool softOvershoot: false
    property real relNominalIndicatorLen: 0.95
    property real relNominalIndicatorWidth: 0.02
    property color vuBackColor: "dimgray"
    property color vuNominalColor: "lawngreen"
    property color vuOvershootColor1: "yellow"
    property color vuOvershootColor2: "red"
    property color vuOvershootIndicatorColor: softOvershoot ? vuNominalColor : vuOvershootColor1
    property real vuEndRadius: horizontal ? height/2 : width/2

    SacVuBase {
        id: vu
        visible: false
        anchors.fill: parent

        nominal: root.nominal
        overshootFactor: root.overshootFactor
        actual: root.actual
        horizontal: root.horizontal
        mirror: root.mirror
        relNominalIndicatorLen: root.relNominalIndicatorLen
        relNominalIndicatorWidth: root.relNominalIndicatorWidth
        vuBackColor: root.vuBackColor
        vuNominalColor: root.vuNominalColor
        vuOvershootColor1: root.vuOvershootColor1
        vuOvershootColor2: root.vuOvershootColor2
        vuOvershootIndicatorColor: root.vuOvershootIndicatorColor
        softOvershoot: root.softOvershoot
    }
    Rectangle {
        id: radiusMask
        anchors.fill: parent
        radius: vuEndRadius
        visible: false
    }
    OpacityMask {
        anchors.fill: parent
        source: vu
        maskSource: radiusMask
    }
}

