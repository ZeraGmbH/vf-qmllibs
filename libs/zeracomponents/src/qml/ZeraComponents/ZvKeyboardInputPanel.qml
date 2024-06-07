import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.VirtualKeyboard 2.14

InputPanel {
    id: root
    // optional external customization:
    property bool showVirtualKeyboard: true
    property var flickable
    property var overlayAnimation

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.bottomMargin: -parent.height * 0.035
    anchors.rightMargin: -parent.width * 0.035
    anchors.leftMargin: anchors.rightMargin
    property bool textEntered: Qt.inputMethod.visible
    opacity: 0
    NumberAnimation on opacity {
        id: keyboardOpacityAnimation
        onStarted: {
            if(to === 1)
                root.visible = showVirtualKeyboard
        }
        onFinished: {
            if(to === 0)
                root.visible = false
        }
    }
    onTextEnteredChanged: {
        var rectInput = Qt.inputMethod.anchorRectangle
        if(textEntered) {
            if(showVirtualKeyboard) {
                if(rectInput.bottom > root.y) {
                    // shift flickable (normal elements)
                    if(flickable !== undefined) {
                        flickable.animation.to = rectInput.bottom - root.y + 10
                        flickable.animation.start()
                    }
                    // shift overlay (Popup)
                    if(overlayAnimation !== undefined) {
                        overlayAnimation.to = -(rectInput.bottom - root.y + 10)
                        overlayAnimation.start()
                    }
                }
                keyboardOpacityAnimation.to = 1
                keyboardOpacityAnimation.duration = 500
                keyboardOpacityAnimation.start()
            }
        }
        else {
            if(flickable !== undefined && flickable.contentY !== 0) {
                // shift everything back
                flickable.animation.to = 0
                flickable.animation.start()
                if(overlayAnimation !== undefined) {
                    overlayAnimation.to = 0
                    overlayAnimation.start()
                }
            }
            keyboardOpacityAnimation.to = 0
            keyboardOpacityAnimation.duration = 0
            keyboardOpacityAnimation.start()
        }
    }
}
