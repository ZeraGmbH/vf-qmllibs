import QtQuick 2.0
import QtQuick.Controls 2.0
import VeinEntity 1.0
import ZeraComponents 1.0

ZComboBox {
    // two dim array 1st: array units 2nd: array of factors
    property var arrEntries: [[]]
    property real currentFactor: arrEntries[1][targetIndex]
    arrayMode: true
    model: arrEntries[0]
}
