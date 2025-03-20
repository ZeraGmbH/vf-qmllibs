import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import ZeraLocale 1.0
import ZeraTranslation 1.0
import Timedate 1.0
import ZeraFa 1.0

RowLayout {
    id: timezoneRow
    TimedateModels { id: timedateModels }
    property real pointSize: height * 0.3
    ComboBox {
        id: regions
        Layout.fillWidth: true
        Layout.fillHeight: true
        font.pointSize: pointSize

        model: timedateModels.regionModel
        textRole: "regiontranslated"

        // Enlightment on how to do this with binding only is welcome
        readonly property int modelIndex: model.selectedIndex
        onCurrentIndexChanged: { model.selectedIndex = currentIndex }
        onModelIndexChanged: { currentIndex = modelIndex }
    }
    ComboBox {
        id: cities
        Layout.fillWidth: true
        Layout.fillHeight: true
        font.pointSize: pointSize

        model: timedateModels.cityModel
        textRole: "citytranslated"

        // Enlightment on how to do this with binding only is welcome
        readonly property int modelIndex: model.selectedIndex
        onCurrentIndexChanged: { model.selectedIndex = currentIndex }
        onModelIndexChanged: { currentIndex = modelIndex }
    }
    Row {
        id: buttonRow
        Layout.preferredWidth: timezoneRow.height * 2
        Layout.fillHeight: true
        spacing: 4
        Button {
            id: buttonClearSelection
            text: FA.fa_undo
            font.pointSize: pointSize
            height: buttonRow.height
            width: height
            enabled: timedateModels.canUndoTimezone
            onClicked: timedateModels.doUndoTimezone()
        }
        Button {
            id: buttonApplySelection
            text: FA.fa_check
            Material.foreground: Material.accentColor
            font.pointSize: pointSize
            height: buttonRow.height
            width: height
            enabled: timedateModels.canApplyTimezone
            onClicked: timedateModels.doApplyTimezone()
        }
    }
}
