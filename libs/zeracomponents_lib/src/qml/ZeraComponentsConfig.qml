pragma Singleton
import QtQuick 2.0
import QmlHelpersConfig 1.0

// Container with defaults for all settings ZeraComponents uses. To make changes
// or make settings persistent, bind them to other properties
//
Item {
    // margin properties
    property real standardMargin: 0
    property real standardTextHorizMargin: 8
    property real standardTextBottomMargin: 8
}
