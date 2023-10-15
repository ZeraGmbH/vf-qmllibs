import QtQuick 2.14
import QtQuick.Controls 2.14

Rectangle {
    property real indicatorWith: (horizontal ? parent.width : parent.height) * relIndicatorWidth
    property real indicatorLen: (horizontal ? parent.height : parent.width) * relIndicatorLen
    property real indicatorStart: ((horizontal ? parent.height : parent.width)-indicatorLen)/2
    radius: indicatorWith/2

    readonly property real xFactor: !mirror ? overshootInvers : 1-overshootInvers
    x: horizontal ? parent.width*xFactor - indicatorWith/2 : indicatorStart
    width: horizontal ? indicatorWith : indicatorLen
    readonly property real yFactor: !mirror ? overshootLen : 1-overshootLen
    y:  horizontal ? indicatorStart : parent.height * yFactor - indicatorWith/2
    height: horizontal ? indicatorLen : indicatorWith
}
