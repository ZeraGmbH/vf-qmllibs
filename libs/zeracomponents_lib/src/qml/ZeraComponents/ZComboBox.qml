import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

/**
  * @b A combo box implementation that can use JS arrays as model and is able to layout the content in a grid, displaying all items at once (if possible)
  */
Rectangle {
    id: root

    property alias headerComponent: headerLoader.sourceComponent
    readonly property alias headerItem: headerLoader.item

    readonly property int count: (model !==undefined) ? (arrayMode===true ? fakeModel.count : model.count) : 0;
    property int currentIndex;
    property int targetIndex;
    property string currentText;
    property string selectedText;
    property real contentRowWidth: width;
    property real contentRowHeight: height;
    property int contentMaxRows: 0
    property real fontSize: 18;
    property bool centerVertical: false
    property real centerVerticalOffset: 0;
    //used when the displayed text should only change from external value changes
    property bool automaticIndexChange: false
    //support for QML ListModel and JS array
    property bool arrayMode: false
    property var model: [];
    property var modelLength;
    readonly property bool modelInitialized: arrayMode === true && model.length>0;
    property int displayRows: contentMaxRows <= 0 || contentMaxRows > count ? count : contentMaxRows
    property int displayColums: Math.ceil(count/displayRows)
    onModelInitializedChanged: updateFakeModel();

    color: Qt.darker(Material.frameColor, (activeFocus ? 1.25 : 2.0)) //buttonPressColor
    //border.color: Material.dropShadowColor
    opacity: enabled ? 1.0 : 0.7
    radius: 4
    activeFocusOnTab: true

    function updateFakeModel() {
        if(modelInitialized === true) {
            fakeModel.clear();
            for(var i=0; i<model.length; i++) {
                fakeModel.append({"text":model[i]})
            }
        }
        modelLength = model.length;
    }


    function updateCurrentText() {
        if(root.arrayMode) {
            if(root.count> targetIndex && targetIndex >= 0) {
                root.currentText = fakeModel.get(targetIndex).text;
            }
        }
        else {
            if(root.count>0 && targetIndex >= 0) {
                root.currentText = root.model.get(targetIndex).text;
            }
        }
    }

    // overrideable - we do not want to depend on ZeraTranslation here
    function translateText(text){
        return text;
    }

    onCountChanged: {
        updateCurrentText()
    }
    onCurrentIndexChanged: {
        targetIndex = currentIndex;
    }
    onTargetIndexChanged: {
        updateCurrentText()
    }
    onModelChanged: {
        if(model) {
            updateFakeModel();
        }
        selectionDialog.close()
    }

    // List view does not support JS arrays
    ListModel {
        id: fakeModel
    }
    Item {
        anchors.fill: parent
        anchors.rightMargin: parent.width/5
        Label {
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.verticalCenter: parent.verticalCenter
            text: {
                var retVal = "";
                if(root.currentText !== undefined) {
                    retVal = translateText(root.currentText)
                }
                return retVal;
            }
            font.pixelSize: root.fontSize
        }
    }
    Label {
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        text: "▼"
        textFormat: Text.PlainText
        font.pixelSize: root.fontSize/2
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(root.enabled && root.count > 0) {
                root.focus = true // here focus is intended
                selectionDialog.open()
            }
        }
    }

    Popup {
        id: selectionDialog
        background: Item {} //remove background rectangle
        property int heightOffset: (root.centerVertical ? -popupElement.height/2 : 0) + root.centerVerticalOffset
        property int widthOffset: - 0.5 * contentRowWidth * (displayColums - 1)

        closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape
        onClosed: {
            root.focus = false
        }

        y:  -15 + heightOffset
        x: -15 + widthOffset

        Rectangle {
            id: popupElement
            width: contentRowWidth * displayColums + comboView.anchors.margins*2
            // note: additional 0.1 avoids GridView startin next column in some cases
            height: contentRowHeight * displayRows + comboView.anchors.margins*2 + 0.1 +
                    headerLoader.height + headerLoader.anchors.margins
            color: Material.backgroundColor //used to prevent opacity leak from Material.dropShadowColor of the delegates
            Rectangle {
                anchors.fill: parent
                color: Material.dropShadowColor
                opacity: 1
                radius: 8
            }
            Loader {
                id: headerLoader
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: height > 0 ? 2 : 0
                active: true
            }
            GridView {
                id: comboView
                anchors.top: headerLoader.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 2

                boundsBehavior: ListView.StopAtBounds

                //adding some space here is the same as "spacing: x" is in other components
                cellHeight: root.contentRowHeight
                cellWidth: root.contentRowWidth

                flow: GridView.FlowTopToBottom

                //need to convert the array to a model
                model: (root.arrayMode===true) ? fakeModel : root.model;

                NumberAnimation on opacity {
                    id: fadeOutAnimation
                    running: false
                    from: 1.0
                    to: 0.4
                    duration: 1250
                    onFinished: {
                        // hacky rewind to initial state
                        start(); stop()
                        selectionDialog.close()
                    }
                }

                delegate: Rectangle {

                    color: (root.targetIndex === index) ? Material.accent : Qt.darker(Material.frameColor) //buttonPressColor
                    border.color: Material.dropShadowColor

                    height: root.contentRowHeight
                    width: root.contentRowWidth
                    radius: 4

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            if(!fadeOutAnimation.running) {
                                if(root.targetIndex !== index) {
                                    var refreshSelectedText = false;

                                    if(root.automaticIndexChange) {
                                        refreshSelectedText = root.selectedText===model.text
                                        root.selectedText = model.text
                                    }
                                    else {
                                        root.targetIndex = index;
                                        root.currentText = model.text;
                                        refreshSelectedText = root.selectedText===root.currentText;
                                        root.selectedText = root.currentText;
                                    }
                                    if(refreshSelectedText) {
                                        /// @DIRTYHACK: this is NOT redundant, it's an undocumented function to notify of the value change that is otherwise ignored by QML
                                        root.selectedTextChanged();
                                    }
                                    if(headerLoader.height > 0) {
                                        fadeOutAnimation.start()
                                    }
                                    else {
                                        selectionDialog.close()
                                    }
                                }
                                else { // no change of selection
                                    selectionDialog.close()
                                }
                            }
                        }
                    }

                    Label {
                        anchors.centerIn: parent
                        text: {
                            var retVal = "";
                            if(model.text !== undefined) {
                                retVal = translateText(model.text)
                            }
                            return retVal;
                        }

                        font.pixelSize: root.fontSize
                    }
                }
            }
        }
    }
}
