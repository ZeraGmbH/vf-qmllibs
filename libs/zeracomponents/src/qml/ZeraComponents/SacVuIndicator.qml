import QtQuick 2.14
import QtQuick.Controls 2.14

Rectangle {
    property real relPosInVu

    // Lazy: we assume variables:
    // horizontal, mirror, relIndicatorWidth, relIndicatorLen
    // available
    readonly property real indicatorWith: (horizontal ? parent.width : parent.height) * relIndicatorWidth
    readonly property real indicatorLen: (horizontal ? parent.height : parent.width) * relIndicatorLen
    readonly property real indicatorStart: ((horizontal ? parent.height : parent.width)-indicatorLen)/2
    radius: indicatorWith/2

    function xor(a, b) {
        if(a !== b)
            return true
        return false
    }
    readonly property real positionInVu: xor(horizontal, mirror) ? relPosInVu : 1-relPosInVu
    x: horizontal ? parent.width*positionInVu - indicatorWith/2 : indicatorStart
    width: horizontal ? indicatorWith : indicatorLen
    y:  horizontal ? indicatorStart : parent.height*positionInVu - indicatorWith/2
    height: horizontal ? indicatorLen : indicatorWith
}
