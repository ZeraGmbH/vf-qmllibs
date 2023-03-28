import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Material 2.14
import QtQuick.VirtualKeyboard 2.14
import QtQuick.VirtualKeyboard.Settings 2.14
import ZeraComponents 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 960
    height: 480
    title: qsTr("Virtual Keyboard Example")

    Material.theme: Material.Dark
    Material.accent: Material.color(Material.Green)

    Flickable {
        id: flickable
        anchors.fill: parent
        contentWidth: parent.width;
        contentHeight: parent.height+inputPanel.realHeight
        boundsBehavior: Flickable.StopAtBounds
        interactive: false
        NumberAnimation on contentY
        {
            duration: 300
            id: flickableAnimation
        }
        // Select language
        ComboBox {
            id: langCombo
            width: 200
            model: [ "en_GB", "en_US", "de_DE", "fr_FR" ]
            onCurrentTextChanged: {
                VirtualKeyboardSettings.locale = langCombo.currentText
            }
            Component.onCompleted: {
                VirtualKeyboardSettings.locale = langCombo.currentText
            }
        }
        Label {
            id: labelEntered
            anchors.left: langCombo.right
            anchors.leftMargin: 5
            anchors.right: parent.right
            height: langCombo.height
            verticalAlignment: "AlignVCenter"
            onTextChanged: animation.start()
            ColorAnimation on color {
                id: animation
                from: "red"
                to: "white"
                duration: 300
            }
        }

        // Dummy test content
        ListView{
            id: listViewControls
            anchors.top: langCombo.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            model: 11
            interactive: false
            delegate: RowLayout {
                id: rowLayout
                height: 40
                readonly property bool delayed: parseInt(modelData, 10) % 2 === 0
                function doApplyAndShow(text) {
                    labelEntered.text = "Entered: " + text
                }
                function doApplyInputOnControl(newText, timer) {
                    if(rowLayout.delayed) {
                        timer.text = newText
                        timer.start()
                        return false
                    }
                    else {
                        rowLayout.doApplyAndShow(newText)
                        return true;
                    }
                }
                // Alphanum text
                ZLineEdit {
                    text: "AlphaNum" + modelData
                    validator: RegExpValidator {
                        regExp: /AlphaNum[0-9].*/
                    }
                    DelayTest {
                        id: alNumTextTimer
                        onTriggered: {
                            doApplyAndShow(text)
                            parent.text = text
                        }
                    }
                    function doApplyInput(newText) {
                        return doApplyInputOnControl(newText, alNumTextTimer)
                    }
                }
                // Integer text
                ZLineEdit {
                    text: modelData
                    validator: IntValidator {
                        bottom: -100
                        top: 100
                    }
                    DelayTest {
                        id: intTextTimer
                        onTriggered: {
                            doApplyAndShow(text)
                            parent.text = text
                        }
                    }
                    function doApplyInput(newText) {
                        return doApplyInputOnControl(newText, intTextTimer)
                    }
                }
                // Double text
                ZLineEdit {
                    text: modelData+"."+modelData
                    validator: ZDoubleValidator {
                        bottom: -100.0
                        top: 100.0
                        decimals: 3
                    }
                    DelayTest {
                        id: doubleTextTimer
                        onTriggered: {
                            doApplyAndShow(text)
                            parent.text = text
                        }
                    }
                    function doApplyInput(newText) {
                        return doApplyInputOnControl(newText, doubleTextTimer)
                    }
                }
                // Integer spin
                ZSpinBox {
                    text: modelData
                    validator: IntValidator {
                        bottom: -100
                        top: 100
                    }
                    DelayTest {
                        id: intSpinTimer
                        onTriggered: {
                            doApplyAndShow(text)
                            parent.text = text
                        }
                    }
                    function doApplyInput(newText) {
                        return doApplyInputOnControl(newText, intSpinTimer)
                    }
                }
                // Double spin
                ZSpinBox {
                    text: modelData+"."+modelData
                    stepSize: 100 // 3 digits(0.001) -> 0.1
                    validator: ZDoubleValidator {
                        bottom: -100.0
                        top: 100.0
                        decimals: 3
                    }
                    DelayTest {
                        id: doubleSpinTimer
                        onTriggered: {
                            doApplyAndShow(text)
                            parent.text = text
                        }
                    }
                    function doApplyInput(newText) {
                        return doApplyInputOnControl(newText, doubleSpinTimer)
                    }
                }
            }
        }
    }
    InputPanel {
         id: inputPanel
         anchors.left: parent.left
         anchors.right: parent.right
         anchors.bottom: parent.bottom
         property bool textEntered: Qt.inputMethod.visible
         // Hmm - why is this necessary?
         property real realHeight: height/1.65
         opacity: 0
         NumberAnimation on opacity
         {
             id: keyboardAnimation
             onStarted: {
                 if(to === 1) {
                     inputPanel.visible = true
                 }
             }
             onFinished: {
                 if(to === 0) {
                     inputPanel.visible = false
                 }
             }
         }
         onTextEnteredChanged: {
             var rectInput = Qt.inputMethod.anchorRectangle
             if (inputPanel.textEntered)
             {
                if(rectInput.bottom > inputPanel.y)
                {
                    flickableAnimation.to = rectInput.bottom - inputPanel.y + 10
                    flickableAnimation.start()
                }
                keyboardAnimation.to = 1
                keyboardAnimation.duration = 500
                keyboardAnimation.start()
             }
             else
             {
                 if(flickable.contentY !== 0)
                 {
                     flickableAnimation.to = 0
                     flickableAnimation.start()
                 }
                 keyboardAnimation.to = 0
                 keyboardAnimation.duration = 0
                 keyboardAnimation.start()
             }
         }
    }
}
