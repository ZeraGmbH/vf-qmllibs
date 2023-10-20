import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14

SacVuDefaults {
    id: root
    SacVuBase {
        id: vu
        anchors.fill: parent

        nominal: root.nominal
        overshootFactor: root.overshootFactor
        actual: root.actual
        horizontal: root.horizontal
        mirror: root.mirror
        relIndicatorLen: root.relIndicatorLen
        relIndicatorWidth: root.relIndicatorWidth
        vuBackColor: root.vuBackColor
        vuNominalColor: root.vuNominalColor
        vuOvershootColor1: root.vuOvershootColor1
        vuOvershootColor2: root.vuOvershootColor2
        vuOvershootIndicatorColor: root.vuOvershootIndicatorColor
        softOvershoot: root.softOvershoot
    }
}

