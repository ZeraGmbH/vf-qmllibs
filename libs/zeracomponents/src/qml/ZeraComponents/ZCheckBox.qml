import QtQuick 2.14
import QtQuick.Controls 2.14

// An auto-resising CheckBox

CheckBox {
    id: root

    property real controlHeight: height * 0.3 // feel free to overbind

    font.pointSize: controlHeight > 0.0 ? controlHeight : 10.5
    function recalcControls() {
        // we create a binding loop somehow
        // fix it by breaking binding and stealing from
        // /usr/lib64/qt5/qml/QtQuick/Controls.2/Material/CheckBox.qml
        implicitHeight = Math.max(implicitBackgroundHeight + topInset + bottomInset,
                                  implicitContentHeight + topPadding + bottomPadding,
                                  implicitIndicatorHeight + topPadding + bottomPadding)
        // box
        indicator.height = controlHeight
        indicator.width = controlHeight
        // checkmark - TODO half checked (we don't use - yet)
        indicator.children[0].height = controlHeight
        indicator.children[0].width = controlHeight
        // mouse hover circle
        indicator.children[2].height = controlHeight*1.75
    }
    onControlHeightChanged: { recalcControls() }
}
