import QtQuick 2.14
import QtQuick.Controls 2.14

SacVuDefaults {
    id: root
    property real undershootFactor: 0.1
    property int undershootAnimationDurationMs: 250
    property color vuZeroIndicatorColor: Qt.lighter(vuBackColor, 5)

    Flickable {
        id: vu
        anchors.fill: parent
        clip: true
        interactive: false

        readonly property bool undershootActive: undershootFactor > 0 && undershootFactor < 1
        readonly property int maxDigitsRel: 3
        readonly property real relActual: Number.parseFloat(actual/nominal).toFixed(maxDigitsRel)
        readonly property bool aboveUndershoot: {
            if(!undershootActive)
                return actual >= 0
            return relActual > undershootFactor
        }
        onAboveUndershootChanged: setFocusPos()
        readonly property bool belowUndershoot: {
            if(!undershootActive)
                return actual < 0
            return relActual < -undershootFactor
        }
        onBelowUndershootChanged: setFocusPos()
        property bool positiveIndicatorWithHysteresis: actual >= 0
        function setFocusPos() {
            if(aboveUndershoot && !belowUndershoot)
                positiveIndicatorWithHysteresis = true
            if(!aboveUndershoot && belowUndershoot)
                positiveIndicatorWithHysteresis = false
        }

        readonly property int subVuCount: 2
        readonly property real totalVuLen: subVuCount*overshootFactor
        readonly property real underShootDisplayVuLen: overshootFactor+undershootFactor
        readonly property real undershootMagnifier: undershootActive ? totalVuLen / underShootDisplayVuLen : 1
        readonly property real widthMagnifier: !horizontal ? 1 : undershootMagnifier
        readonly property real heightMagnifier: horizontal ? 1 : undershootMagnifier
        contentWidth: width * widthMagnifier
        contentHeight: height * heightMagnifier
        readonly property real xTargetPos: undershootActive && horizontal && leftLowerVu.xor(positiveIndicatorWithHysteresis, mirror) ? contentWidth-width : 0
        readonly property real yTargetPos: undershootActive && !horizontal && leftLowerVu.xor(positiveIndicatorWithHysteresis, !mirror) ? contentHeight-height : 0
        contentX: xTargetPos
        contentY: yTargetPos
        SacVuBase {
            id: leftLowerVu
            x: 0
            width: parent.width / (horizontal ? vu.subVuCount : 1)
            y: horizontal ? 0 : height
            height: parent.height / (horizontal ? 1 : vu.subVuCount)

            nominal: root.nominal
            overshootFactor: root.overshootFactor
            actual: root.actual * (root.mirror ? 1 : -1)
            horizontal: root.horizontal
            mirror: true
            relIndicatorLen: root.relIndicatorLen
            relIndicatorWidth: root.relIndicatorWidth / vu.undershootMagnifier
            vuBackColor: root.vuBackColor
            vuNominalColor: root.vuNominalColor
            vuOvershootColor1: root.vuOvershootColor1
            vuOvershootColor2: root.vuOvershootColor2
            vuOvershootIndicatorColor: root.vuOvershootIndicatorColor
            softOvershoot: root.softOvershoot
        }
        SacVuBase {
            id: rightUpperVu
            x: horizontal ? parent.width / vu.subVuCount : 0
            width: parent.width / (horizontal ? vu.subVuCount : 1)
            y: 0
            height: parent.height / (horizontal ? 1 : vu.subVuCount)

            nominal: root.nominal
            overshootFactor: root.overshootFactor
            actual: root.actual * (root.mirror ? -1 : 1)
            horizontal: root.horizontal
            mirror: false
            relIndicatorLen: root.relIndicatorLen
            relIndicatorWidth: root.relIndicatorWidth / vu.undershootMagnifier
            vuBackColor: root.vuBackColor
            vuNominalColor: root.vuNominalColor
            vuOvershootColor1: root.vuOvershootColor1
            vuOvershootColor2: root.vuOvershootColor2
            vuOvershootIndicatorColor: root.vuOvershootIndicatorColor
            softOvershoot: root.softOvershoot
        }
        SacVuIndicator {
            id: zeroIndicator
            color: vuZeroIndicatorColor

            horizontal: root.horizontal
            mirror: root.mirror
            relPosInVu: 0.5
            relIndicatorLen: root.relIndicatorLen
            relIndicatorWidth: root.relIndicatorWidth * 0.5 / vu.undershootMagnifier
        }
    }
}
