import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import ZeraLocale 1.0
import ZeraTranslation 1.0
import Timedate 1.0

RowLayout {
    id: timezoneRow
    property real comboWidth: 390
    TimedateModels { id: timedateModels }
    ComboBox {
        id: regions
        Layout.fillWidth: true

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

        model: timedateModels.cityModel
        textRole: "citytranslated"

        // Enlightment on how to do this with binding only is welcome
        readonly property int modelIndex: model.selectedIndex
        onCurrentIndexChanged: { model.selectedIndex = currentIndex }
        onModelIndexChanged: { currentIndex = modelIndex }
    }
}
