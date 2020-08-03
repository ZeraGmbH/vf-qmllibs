pragma Singleton
import QtQuick 2.0


// Container with defaults for all settings ZeraHelpers uses. To make changes
// or make settings persistent, bind them to other properties
Item {
    // locale properties
    property string localeName: "en_GB"
    property var locale: Qt.locale(localeName)
}
