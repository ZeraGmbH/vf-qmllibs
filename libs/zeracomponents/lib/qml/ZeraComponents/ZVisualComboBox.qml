import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Controls.Material.impl 2.14
import ZeraThemeConfig 1.0

/**
  * @b A picture based combo box implementation that can use JS arrays as model and is able to layout the content in a grid, displaying all items at once (if possible)
  */
Rectangle {
    id: root

    property var popupBorderItem: Overlay.overlay
    property bool popupKeepHorizontalSize: false
    //supports only arrays, but the property is kept to remain compatible with the ZComboBox, maybe it is possible to join both into one type that can handle both use cases?
    readonly property bool arrayMode: true
    property int count: (model !==undefined) ? (arrayMode===true ? fakeModel.count : model.count) : 0;
    property int currentIndex;
    property int targetIndex;
    property string currentText;
    property string selectedText;
    property var model: [];
    property int displayRows: contentMaxRows <= 0 || contentMaxRows > count ? count : contentMaxRows
    property int displayColumns: Math.ceil(count/displayRows)
    property var imageModel: [];
    property int contentMaxRows: 0

    function openDropList() {
        if(enabled && count > 0) {
            getPositionInParent()
            focus = true // here focus is intended
            comboPopup.open()
        }
    }
    //used when the displayed text should only change from external value changes
    property bool automaticIndexChange: false
    property bool imageMipmap: true;
    readonly property bool modelInitialized: arrayMode === true && model.length>0 && imageModel.length>0;
    onModelInitializedChanged: updateFakeModel();

    // List view does not support JS arrays
    ListModel {
        id: fakeModel
    }
    function updateFakeModel() {
        if(modelInitialized === true) {
            fakeModel.clear();
            for(var i=0; i<model.length; i++) {
                fakeModel.append({"text":model[i], "source":imageModel[i]})
            }
        }
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

    onCurrentIndexChanged: {
        targetIndex = currentIndex;
    }
    onCountChanged: {
        updateCurrentText()
    }
    onImageModelChanged: {
        fakeModel.clear();
        if(model && imageModel) {
            comboPopup.close()
        }
    }
    onModelChanged: {
        if(model && imageModel) {
            updateFakeModel();
            comboPopup.close()
        }
    }
    onTargetIndexChanged: {
        updateCurrentText()
    }

    color: enabled ? ZTC.buttonColor : ZTC.buttonColorDisabled
    radius: 4

    layer.enabled: enabled
    layer.effect: ElevationEffect {
        elevation: 2
    }

    Image {
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        source:  modelInitialized === true ? fakeModel.get(targetIndex).source : undefined
        fillMode: Image.PreserveAspectFit
        mipmap: true
    }
    Label {
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: root.height > 0 ? root.height * 0.2 : 10
        text: "▼"
        textFormat: Text.PlainText
    }

    MouseArea {
        anchors.fill: parent
        onClicked: openDropList()
    }

    function getPositionInParent() {
        var l = mapToItem(comboPopup.parent, width/2, height/2)
        comboPopup.posXInApplication = l.x
        comboPopup.posYInApplication = l.y
    }
    readonly property real popupMargin: 2
    Popup {
        id: comboPopup
        background: Item {} //remove background rectangle - is draws at unexpected upper left corner

        closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape
        onClosed: root.focus = false

        parent: popupBorderItem
        leftPadding: 0
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0
        property real posXInApplication
        property real posYInApplication
        width: root.width * (popupKeepHorizontalSize ? 1 : displayColumns)
        x: {
            let posX = posXInApplication - width/2
            if(posX < 0)
                posX = 0
            else if(posX + width > parent.width)
                posX = parent.width - width
            return posX
        }
        height: root.height * displayRows //+ headerLoader.height
        y: {
            let posY = posYInApplication - height/2
            if(posY < 0)
                posY = 0
            else if(posY + height > parent.height)
                posY = parent.height - height
            return posY
        }

        Rectangle {
            id: popupElement
            width: comboPopup.width
            height: comboPopup.height
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
                anchors.margins: popupMargin

                boundsBehavior: ListView.StopAtBounds

                cellHeight: height / displayRows
                cellWidth: width / displayColumns

                flow: GridView.FlowTopToBottom

                //need to convert the array to a model
                model: (root.arrayMode===true) ? fakeModel : root.model;
                delegate: Rectangle {
                    color: (root.targetIndex === index) ? Material.accent : ZTC.buttonColor
                    border.color: Material.dropShadowColor

                    height: comboView.cellHeight
                    width: comboView.cellWidth
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
                            comboPopup.close()
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
