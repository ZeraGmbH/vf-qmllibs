import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

/**
  * @b A picture based combo box implementation that can use JS arrays as model and is able to layout the content in a grid, displaying all items at once (if possible)
  */
Rectangle {
    id: root

    //List view does not support JS arrays
    ListModel {
        id: fakeModel
    }

    //supports only arrays, but the property is kept to remain compatible with the ZComboBox, maybe it is possible to join both into one type that can handle both use cases?
    readonly property bool arrayMode: true
    property int count: (model !==undefined) ? (arrayMode===true ? fakeModel.count : model.count) : 0;
    property int currentIndex;
    property int targetIndex;
    property string currentText;
    property string selectedText;
    property var model: [];
    property var modelLength;
    property var imageModel: [];
    property real contentRowWidth: width;
    property real contentRowHeight: height;
    property int contentMaxRows: 0
    property bool centerVertical: false
    property real centerVerticalOffset: 0;
    //used when the displayed text should only change from external value changes
    property bool automaticIndexChange: false
    property bool imageMipmap: true;
    readonly property bool modelInitialized: arrayMode === true && model.length>0 && imageModel.length>0;
    onModelInitializedChanged: updateFakeModel();
    property alias popup :selectionDialog

    function updateFakeModel() {
        if(modelInitialized === true) {
            fakeModel.clear();
            for(var i=0; i<model.length; i++) {
                fakeModel.append({"text":model[i], "source":imageModel[i]})
            }
        }
        modelLength = model.length;
    }

    readonly property int displayRows: contentMaxRows <= 0 || contentMaxRows > count ? count : contentMaxRows
    readonly property int displayColums: Math.ceil(count/displayRows)

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

    onCurrentIndexChanged: {
        targetIndex = currentIndex;
    }
    onCountChanged: {
        updateCurrentText()
    }
    onImageModelChanged: {
        fakeModel.clear();
        if(model && imageModel) {
            selectionDialog.close()
        }
    }
    onModelChanged: {
        if(model && imageModel) {
            updateFakeModel();
            selectionDialog.close()
        }
    }
    onTargetIndexChanged: {
        updateCurrentText()
    }

    color: Qt.darker(Material.frameColor) //buttonPressColor
    //border.color: Material.dropShadowColor
    opacity: enabled ? 1.0 : 0.7
    radius: 4

    Image {
        anchors.fill: parent
        anchors.topMargin: 2
        anchors.bottomMargin: 2
        anchors.rightMargin: parent.width/5
        source:  modelInitialized === true ? fakeModel.get(targetIndex).source : undefined
        fillMode: Image.PreserveAspectFit
        mipmap: true
    }
    Label {
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: contentRowHeight > 0 ? contentRowHeight * 0.2 : 10
        text: "▼"
        textFormat: Text.PlainText
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

        property int heightOffset: (root.centerVertical ? -popupElement.height/2 : 0) + root.centerVerticalOffset
        property int widthOffset: - contentRowWidth * (displayColums - 1)
        background: Item {} //remove background rectangle
        closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape
        onClosed: {
            root.focus = false
        }

        y:  -15 + heightOffset
        x: -15 + widthOffset

        Rectangle {
            id: popupElement
            width: root.contentRowWidth * displayColums + comboView.anchors.margins*2
            height: root.contentRowHeight * displayRows + comboView.anchors.margins*2
            color: Material.backgroundColor //used to prevent opacity leak from Material.dropShadowColor of the delegates
            Rectangle {
                anchors.fill: parent
                color: Material.dropShadowColor
                opacity: 1
                radius: 8
            }
            GridView {
                id: comboView
                anchors.fill: parent
                anchors.margins: 2

                boundsBehavior: ListView.StopAtBounds

                //adding some space here is the same as "spacing: x" is in other components
                cellHeight: root.contentRowHeight
                cellWidth: root.contentRowWidth

                flow: GridView.FlowTopToBottom

                //need to convert the array to a model
                model: (root.arrayMode===true) ? fakeModel : root.model;
                delegate: Rectangle {

                    color: (root.targetIndex === index) ? Material.accent : Qt.darker(Material.frameColor) //buttonPressColor
                    border.color: Material.dropShadowColor

                    height: root.contentRowHeight
                    width: root.contentRowWidth
                    radius: 4

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
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
                            }
                            selectionDialog.close()
                        }
                    }

                    Image {
                        anchors.fill: parent
                        anchors.topMargin: 2
                        anchors.bottomMargin: 2
                        source: model.source
                        fillMode: Image.PreserveAspectFit
                        mipmap: root.imageMipmap
                    }
                }
            }
        }
    }
}
