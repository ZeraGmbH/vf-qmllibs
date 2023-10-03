import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14

/**
  * @b A combo box implementation that can use JS arrays as model and is able to layout the content in a grid, displaying all items at once (if possible)
  */
Rectangle {
    id: root

    // removed soon
    property bool centerVertical: false
    property real centerVerticalOffset: 0;
    property real contentRowWidth: width;
    property real contentRowHeight: height;

    property alias headerComponent: headerLoader.sourceComponent
    readonly property alias headerItem: headerLoader.item
    property alias popup: comboPopup
    readonly property int count: (model !==undefined) ? (arrayMode===true ? fakeModel.count : model.count) : 0;
    property int currentIndex;
    property int targetIndex;
    property string currentText;
    property string selectedText;
    property real pointSize: height > 0 ? height * 0.3 : 10
    property int contentMaxRows: 0
    property bool fadeOutOnClose: false
    property bool flashOnContentChange: false

    function openDropList() {
        if(enabled && count > 0) {
            getPositionInParent()
            focus = true // here focus is intended
            comboPopup.open()
        }
    }

    //used when the displayed text should only change from external value changes
    property bool automaticIndexChange: false
    //support for QML ListModel and JS array
    property bool arrayMode: false
    property var model: [];
    readonly property bool modelInitialized: arrayMode === true && model.length>0;
    property int displayRows: contentMaxRows <= 0 || contentMaxRows > count ? count : contentMaxRows
    property int displayColumns: Math.ceil(count/displayRows)
    onModelInitializedChanged: updateFakeModel();

    color: Qt.darker(Material.frameColor, (activeFocus ? 1.25 : 2.0)) //buttonPressColor
    property var textColor: Material.foreground
    opacity: enabled ? 1.0 : 0.7
    radius: 4
    activeFocusOnTab: true

    function updateFakeModel() {
        if(modelInitialized === true) {
            fakeModel.clear();
            for(var i=0; i<model.length; i++)
                fakeModel.append({"text":model[i]})
        }
    }

    function updateCurrentText() {
        if(root.arrayMode) {
            if(root.count> targetIndex && targetIndex >= 0)
                root.currentText = fakeModel.get(targetIndex).text
        }
        else if(root.count>0 && targetIndex >= 0)
            root.currentText = root.model.get(targetIndex).text
    }

    // overrideable - we do not want to depend on ZeraTranslation here
    function translateText(text){
        return text;
    }

    onCountChanged: updateCurrentText()
    onCurrentIndexChanged: targetIndex = currentIndex
    onTargetIndexChanged: updateCurrentText()
    onModelChanged: {
        if(model) {
            updateFakeModel();
            if(flashOnContentChange)
                comboRipple.startFlash()
        }
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
                if(root.currentText !== undefined)
                    retVal = translateText(root.currentText)
                return retVal;
            }
            font.pointSize: pointSize
            color: textColor
        }
    }
    Label {
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        text: "▼"
        textFormat: Text.PlainText
        font.pointSize: root.height > 0 ? root.height * 0.2 : 10
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

        parent: ApplicationWindow.overlay
        leftPadding: 0
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0
        property real posXInApplication
        property real posYInApplication
        width: root.width * displayColumns
        x: {
            let posX = posXInApplication - width/2
            if(posX < 0)
                posX = 0
            else if(posX + width > parent.width)
                posX = parent.width - width
            return posX
        }
        height: root.height * displayRows + headerLoader.height
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
            Loader {
                id: headerLoader
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: height > 0 ? popupMargin : 0
                active: true
            }
            GridView {
                id: comboView
                anchors.top: headerLoader.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: popupMargin

                boundsBehavior: ListView.StopAtBounds

                cellHeight: height / displayRows
                cellWidth: width / displayColumns

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
                        comboPopup.close()
                    }
                }

                delegate: Rectangle {
                    color: (root.targetIndex === index) ? Material.accent : Qt.darker(Material.frameColor) //buttonPressColor
                    border.color: Material.dropShadowColor

                    height: comboView.cellHeight
                    width: comboView.cellWidth
                    radius: 4

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(!fadeOutAnimation.running) {
                                if(root.targetIndex !== index) {
                                    let refreshSelectedText = false
                                    if(root.automaticIndexChange) {
                                        refreshSelectedText = root.selectedText === model.text
                                        root.selectedText = model.text
                                    }
                                    else {
                                        root.targetIndex = index
                                        root.currentText = model.text
                                        refreshSelectedText = root.selectedText === root.currentText
                                        root.selectedText = root.currentText
                                    }
                                    if(refreshSelectedText)
                                        /// @DIRTYHACK: this is NOT redundant, it's an undocumented function to notify of the value change that is otherwise ignored by QML
                                        root.selectedTextChanged()
                                    if(fadeOutOnClose)
                                        fadeOutAnimation.start()
                                    else
                                        comboPopup.close()
                                }
                                else // no change of selection
                                    comboPopup.close()
                            }
                        }
                    }
                    Label {
                        anchors.centerIn: parent
                        text: {
                            var retVal = ""
                            if(model.text !== undefined)
                                retVal = translateText(model.text)
                            return retVal
                        }
                        font.pointSize: pointSize
                    }
                }
            }
        }
    }
    ZFlashingRipple {
        anchor: root
        id: comboRipple
    }
}
