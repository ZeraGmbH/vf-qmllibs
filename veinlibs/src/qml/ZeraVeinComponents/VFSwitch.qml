import QtQuick 2.14
import QtQuick.Controls 2.14
import ZeraComponents 1.0

ZCheckBox {
    id: root
    property QtObject entity
    property string controlPropertyName

    onCheckedChanged: {
        if(checked !== entity[controlPropertyName])
            entity[controlPropertyName] = checked
    }
    QtObject {
        readonly property bool intermediate: entity[controlPropertyName]
        onIntermediateChanged: {
            if(checked !== intermediate)
                checked = intermediate
        }
    }
}
