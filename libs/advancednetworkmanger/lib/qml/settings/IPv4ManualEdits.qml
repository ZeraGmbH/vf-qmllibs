import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import anmsettings 1.0
import ZeraComponents 1.0
import ZeraTranslation 1.0

Item {
    property alias ipv4: ipv4
    property alias sub4: sub4

    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.right: parent.right
    height: 2*rowHeight
    ZLineEdit {
        id: ipv4
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        description.text: Z.tr("IP:")
        description.width: labelWidth
        placeholderText: enabled ? Z.tr("Enter IP address e.g 192.168.1.1") : ""
        selectAllOnFocus: true
        height: rowHeight
        pointSize: rootItm.pointSize
        validator: RegularExpressionValidator { regularExpression: /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/}
        enabled: backend.ipFieldsEnabled(ipv4Mode.currentIndex)
        ConnectionTreeInterface { id: connTreeIface }
        // overrides
        function doApplyInput(newText) {
            backend.ipv4 = newText
            let submask = connTreeIface.deduceSubNetMaskIpv4(newText)
            if (submask !== "")
                sub4.setMask(submask)
            else
                Qt.callLater(sub4.textField.forceActiveFocus)
            return true
        }
        function activeFocusChange(actFocus) {
            baseActiveFocusChange(actFocus)
            // hack: force virtual keyboard numeric with decimal point
            textField.inputMethodHints = Qt.ImhFormattedNumbersOnly
            hackVkFocusHelper.hackVKeyboardSettings(actFocus)
        }
    }
    ZLineEdit {
        id: sub4
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        description.text: Z.tr("Subnetmask:")
        selectAllOnFocus: true
        placeholderText: enabled ? Z.tr("Enter subnet mask e.g 255.255.255.0") : ""
        description.width: labelWidth
        height: rowHeight
        pointSize: rootItm.pointSize
        validator: RegularExpressionValidator { regularExpression: /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/}
        enabled: backend.ipFieldsEnabled(ipv4Mode.currentIndex)
        function setMask(mask) {
            text = mask
            backend.ipv4Sub = mask
        }
        // overrides
        function doApplyInput(newText) {
            backend.ipv4Sub = newText
            return true
        }
        function activeFocusChange(actFocus) {
            baseActiveFocusChange(actFocus)
            // hack: force virtual keyboard numeric with decimal point
            textField.inputMethodHints = Qt.ImhFormattedNumbersOnly
            hackVkFocusHelper.hackVKeyboardSettings(actFocus)
        }
    }
}
