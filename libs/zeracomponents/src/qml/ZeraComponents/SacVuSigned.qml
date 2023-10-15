import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14

SacVuDefaults {
    id: root
    property real vuEndRadius: horizontal ? height/2 : width/2
    Item {
        id: vu
        visible: false
        anchors.fill: parent
        SacVuBase {
            id: leftLowerVu
            x: 0
            width: parent.width / (horizontal ? 2 : 1)
            y: horizontal ? 0 : height
            height: parent.height / (horizontal ? 1 : 2)

            nominal: root.nominal
            overshootFactor: root.overshootFactor
            actual: root.actual * (root.mirror ? 1 : -1)
            horizontal: root.horizontal
            mirror: true
            relNominalIndicatorLen: root.relNominalIndicatorLen
            relNominalIndicatorWidth: root.relNominalIndicatorWidth
            vuBackColor: root.vuBackColor
            vuNominalColor: root.vuNominalColor
            vuOvershootColor1: root.vuOvershootColor1
            vuOvershootColor2: root.vuOvershootColor2
            vuOvershootIndicatorColor: root.vuOvershootIndicatorColor
            softOvershoot: root.softOvershoot
        }
        SacVuBase {
            id: rightUpperVu
            x: horizontal ? parent.width / 2 : 0
            width: parent.width / (horizontal ? 2 : 1)
            y: 0
            height: parent.height / (horizontal ? 1 : 2)

            nominal: root.nominal
            overshootFactor: root.overshootFactor
            actual: root.actual * (root.mirror ? -1 : 1)
            horizontal: root.horizontal
            mirror: false
            relNominalIndicatorLen: root.relNominalIndicatorLen
            relNominalIndicatorWidth: root.relNominalIndicatorWidth
            vuBackColor: root.vuBackColor
            vuNominalColor: root.vuNominalColor
            vuOvershootColor1: root.vuOvershootColor1
            vuOvershootColor2: root.vuOvershootColor2
            vuOvershootIndicatorColor: root.vuOvershootIndicatorColor
            softOvershoot: root.softOvershoot
        }
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

