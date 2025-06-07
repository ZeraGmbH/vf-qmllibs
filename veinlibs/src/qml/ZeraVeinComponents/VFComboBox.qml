import QtQuick 2.0
import QtQuick.Controls 2.0
import ZeraComponents 1.0
import ZeraTranslation 1.0

ZComboBox {
    property QtObject entity
    property string controlPropertyName
    property bool entityIsIndex: false

    function setInitialIndex() {
        if(entity && model) {
            if(entityIsIndex !== true)
                currentIndex = model.indexOf(entity[controlPropertyName]);
            else
                currentIndex = entity[controlPropertyName];
        }
    }

    automaticIndexChange: true

    onEntityChanged: setInitialIndex();
    onEntityIsIndexChanged: setInitialIndex();
    onModelChanged: setInitialIndex();
    onSelectedTextChanged: {
        if(entityIsIndex !== true) {
            if(entity[controlPropertyName] !== selectedText)
                entity[controlPropertyName] = selectedText
        }
        else {
            if(entity[controlPropertyName] !== model.indexOf(selectedText))
                entity[controlPropertyName] = model.indexOf(selectedText)
        }
    }

    QtObject {
        readonly property int intermediate: {
            if (model && entity && controlPropertyName) {
                if (entityIsIndex !== true)
                    return model.indexOf(entity[controlPropertyName])
                return entity[controlPropertyName]
            }
            return -1
        }
        onIntermediateChanged: {
            if(currentIndex !== intermediate)
                currentIndex = intermediate
        }
    }
}
