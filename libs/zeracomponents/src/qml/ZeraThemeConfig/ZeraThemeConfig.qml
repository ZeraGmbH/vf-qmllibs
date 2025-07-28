pragma Singleton
import QtQuick 2.14
import QtQuick.Controls.Material 2.14

Item {
    property int materialTheme: Material.Dark
    readonly property bool isDarkTheme: materialTheme === Material.Dark

    // Material theme colors
    // stolen from src/imports/controls/material/qquickmaterialstyle.cpp
    property color primaryTextColor: isDarkTheme ? "#FFFFFFFF" : "#DD000000"
    property color buttonColor: isDarkTheme ? "#3FCCCCCC" : "#FFD6D7D7"
    property color buttonColorDisabled: dividerColor

    property color frameColor: isDarkTheme ? "#4cffffff" : "#60000000"
    property color dividerColor: isDarkTheme ? "#484848" : "#DDDDDD" // -> not transparent

    // ZENUX customization
    property var accentColor: isDarkTheme ? "#339966" : Qt.darker("#FFE082", 1.3)
    property var accentColorMoreContrast: isDarkTheme ? "#FFE082" /*Material.Amber*/ : Qt.darker("#FFE082", 1.3)
    property color tableHeaderColor: isDarkTheme ? "#003040" : "#EAEDEE" // -> not transparent
    property color toolbarColor: isDarkTheme ? "#206040" : "#18003040"
}
