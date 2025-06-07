import QtQuick 2.14
import QtQuick.Controls 2.14
import ZeraComponents 1.0

ZCheckBox {
    property QtObject entity
    property string controlPropertyName

    onCheckedChanged: {
        if(checked !== entity[controlPropertyName])
            entity[controlPropertyName] = checked
    }
    QtObject {
        readonly property bool intermediate: {
            if (entity !== undefined)
                return entity[controlPropertyName]
            return false
        }
        onIntermediateChanged: {
            if(checked !== intermediate)
                checked = intermediate
        }
    }
}
