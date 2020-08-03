import QtQuick 2.0
import QtQuick.Controls 2.0
import ZeraComponents 1.0
import ZeraTranslation 1.0

ZComboBox {
  id: root
  property QtObject entity
  property string controlPropertyName
  property bool entityIsIndex: false



  function textProperty(text){
      return Z.tr(text)
  }

  function setInitialIndex() {
    if(entity && model) {
      if(entityIsIndex !== true)
      {
        currentIndex = model.indexOf(entity[controlPropertyName]);
      }
      else
      {
        currentIndex = entity[controlPropertyName];
      }
    }
  }

  automaticIndexChange: true

  onEntityChanged: setInitialIndex();
  onEntityIsIndexChanged: setInitialIndex();
  onModelChanged: setInitialIndex();
  onSelectedTextChanged: {
    if(entityIsIndex !== true)
    {
      if(entity[controlPropertyName] !== selectedText)
      {
        entity[controlPropertyName] = selectedText
      }
    }
    else
    {
      if(entity[controlPropertyName] !== model.indexOf(selectedText))
      {
        entity[controlPropertyName] = model.indexOf(selectedText)
      }
    }
  }

  QtObject {
    property int intermediate: entityIsIndex !== true ? model.indexOf(root.entity[root.controlPropertyName]) : root.entity[root.controlPropertyName];
    onIntermediateChanged: {
      if(root.currentIndex !== intermediate)
      {
        root.currentIndex = intermediate
      }
    }
  }
}
