import QtQuick 2.14
import QtQuick.Controls 2.14

// An auto-resising RadioButton

RadioButton {
    id: root

    property real controlHeight: height * 0.4 // feel free to overbind

    font.pointSize: controlHeight > 0.0 ? controlHeight : 10.5
    function recalcControls() {
        if(controlHeight > 0.0) {
            // we create a binding loop somehow
            // fix it by breaking binding and stealing from
            // /usr/lib64/qt5/qml/QtQuick/Controls.2/Material/RadioButton.qml
            implicitHeight = Math.max(implicitBackgroundHeight + topInset + bottomInset,
                                      implicitContentHeight + topPadding + bottomPadding,
                                      implicitIndicatorHeight + topPadding + bottomPadding)
            // box
            indicator.height = controlHeight
            indicator.width = controlHeight
            // checkmark
            indicator.children[0].height = controlHeight * 0.5
            indicator.children[0].width = controlHeight * 0.5
            // mouse hover circle
            indicator.children[1].height = controlHeight*1.75
        }
    }
    onControlHeightChanged: { recalcControls() }
}
