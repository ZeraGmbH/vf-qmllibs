import QtQuick 2.14
import QtQuick.Controls 2.14
import ZeraComponents 1.0

ZCheckBox {
    id: root
    property QtObject entity
    property string controlPropertyName

    onClicked: {
        var check=!entity[controlPropertyName]
        entity[controlPropertyName] = check;
        //checked=check
    }

    onCheckedChanged: {
        if(checked !== entity[controlPropertyName])
        {
            checked = entity[controlPropertyName];
        }
    }

    QtObject {
        readonly property bool intermediate: entity[controlPropertyName]
        onIntermediateChanged: {
            if(root.checked !== intermediate)
                root.checked = intermediate
        }
    }
}
