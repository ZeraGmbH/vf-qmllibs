import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import ZeraComponentsConfig 1.0
import QmlHelpers 1.0
import ZeraLocale 1.0

Item {
  Layout.alignment: Qt.AlignVCenter
  Layout.minimumWidth: tField.width
  id: root

  // public interface
  property var validator
  property string text: "" // locale C
  property alias textField: tField
  property alias inputMethodHints: tField.inputMethodHints;
  property alias placeholderText: tField.placeholderText;
  property alias readOnly: tField.readOnly
  readonly property bool acceptableInput: hasValidInput()
  property real pointSize: height/2.5
  property bool changeOnFocusLost: true

  // some extra labels (would like to get rid of them...)
  property alias description: descriptionText
  property alias unit: unitLabel

  // overridables
  function doApplyInput(newText) {return true} // (return true: apply immediate)
  function hasAlteredValue() {
    var decimals = isDouble ? validator.decimals : 0
    return TextHelper.hasAlteredValue(isNumeric, isDouble, decimals, tField.text, text)
  }
  function hasValidInput() {
    return tField.acceptableInput && TextHelper.hasValidInput(isDouble, tField.text)
  }
  function discardInput() {
    tField.text = ZLocale.strToLocal(text, isNumeric, isDouble)
  }

  // signal handler
  onTextChanged: {
    discardInput()
  }
  onValidatorChanged: {
    tField.validator = validator
    if(isNumeric) {
      tField.inputMethodHints = Qt.ImhFormattedNumbersOnly
    }
    else {
      tField.inputMethodHints = Qt.ImhNoAutoUppercase
    }
  }
  onLocaleNameChanged: {
    discardInput()
  }

  // bit of a hack to check for IntValidator / DoubleValidator to detect a numeric field
  readonly property bool isNumeric: validator !== undefined && 'bottom' in validator && 'top' in validator
  readonly property bool isDouble: isNumeric && 'decimals' in validator
  readonly property string localeName: ZLocale.localeName
  function applyInput() {
    if(hasValidInput())
    {
      if(hasAlteredValue())
      {
        var newText = ZLocale.strToCLocale(tField.text, isNumeric, isDouble)
        if(doApplyInput(newText)) {
          text = newText
        }
      }
      // we changed text but did not change value
      else {
        discardInput()
      }
    }
    else {
      discardInput()
    }
  }

  // controls
  Label { // compatibility - see comment above
    id: descriptionText
    height: parent.height
    verticalAlignment: Text.AlignVCenter
    font.pointSize: root.pointSize
    anchors.left: parent.left
  }
  TextField {
    id: tField
    anchors.left: descriptionText.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.right: unitLabel.left
    anchors.leftMargin: ZCC.standardTextHorizMargin
    anchors.rightMargin: ZCC.standardTextHorizMargin
    horizontalAlignment: Text.AlignRight
    bottomPadding: ZCC.standardTextBottomMargin
    font.pointSize: root.pointSize

    mouseSelectionMode: TextInput.SelectWords
    selectByMouse: true
    inputMethodHints: Qt.ImhNoAutoUppercase
    onAccepted: {
      if(hasValidInput()) {
        applyInput()
        focus = false
      }
    }
    Keys.onEscapePressed: {
      discardInput()
      focus = false
    }
    /* Avoid QML magic: when the cursor is at start/end position,
       left/right keys are used to change tab. We don't want that */
    Keys.onLeftPressed: {
      if(cursorPosition > 0 || selectedText !== "") {
        event.accepted = false;
      }
    }
    Keys.onRightPressed: {
      if(cursorPosition < text.length || selectedText !== "") {
        event.accepted = false;
      }
    }

    onFocusChanged: {
      if(changeOnFocusLost && !focus) {
        if(hasAlteredValue()) {
          if(hasValidInput()) {
            applyInput()
          }
          else {
            discardInput()
          }
        }
      }
      // Hmm - maybe we should add an option for this...
      /*else {
        selectAll()
      }*/
    }

    Rectangle {
      color: "red"
      opacity: 0.2
      visible: hasValidInput() === false && tField.enabled
      anchors.fill: parent
    }
    Rectangle {
      color: "green"
      opacity: 0.2
      visible: hasValidInput() && tField.enabled && hasAlteredValue()
      anchors.fill: parent
    }
  }
  Label { // compatibility - see comment above
    id: unitLabel
    height: parent.height
    font.pointSize: root.pointSize
    anchors.right: parent.right
    verticalAlignment: Text.AlignVCenter
  }
}
