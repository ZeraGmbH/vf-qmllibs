import QtQuick 2.14
import QtQuick.Controls 2.14

Rectangle {
    property bool horizontal
    property bool mirror
    property real relPosInVu
    property real relIndicatorWidth
    property real relIndicatorLen

    readonly property real indicatorWith: (horizontal ? parent.width : parent.height) * relIndicatorWidth
    readonly property real indicatorLen: (horizontal ? parent.height : parent.width) * relIndicatorLen
    readonly property real indicatorStart: ((horizontal ? parent.height : parent.width)-indicatorLen)/2
    radius: indicatorWith/2

    function xor(a, b) { return a !== b }
    readonly property real positionInVu: xor(horizontal, mirror) ? relPosInVu : 1-relPosInVu
    x: horizontal ? parent.width*positionInVu - indicatorWith/2 : indicatorStart
    width: horizontal ? indicatorWith : indicatorLen
    y:  horizontal ? indicatorStart : parent.height*positionInVu - indicatorWith/2
    height: horizontal ? indicatorLen : indicatorWith
}
