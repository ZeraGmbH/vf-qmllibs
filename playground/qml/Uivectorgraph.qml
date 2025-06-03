import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.12
import uivectorgraphics 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "uivector"

    width: 800
    height: 480

    TabBar {
        id: bar
        width: parent.width
        anchors.top: parent.top
        TabButton {
            text: qsTr("uivectorsettings")
        }
        TabButton {
            text: qsTr("uivectorgraph")
        }
    }

    VisualItemModel{
        id: setModel
        RowLayout{
            Label {
                id: v1set
                text: "U1:"
            }
            TextField{
                id: v1x
                placeholderText: "U1x"
                text: "125"
            }

            TextField{
                id: v1y
                placeholderText: "U1y"
                text: "125"
            }

        }
        RowLayout{
            Label {
                id: v2set
                text: "U2:"
            }
            TextField{
                id: v2x
                placeholderText: "U2x"
            }

            TextField{
                id: v2y
                placeholderText: "U2y"
            }

        }
        RowLayout{
            Label {
                id: v3set
                text: "U3:"
            }

            TextField{
                id: v3x
                placeholderText: "U3x"
            }

            TextField{
                id: v3y
                placeholderText: "U3y"
            }

        }
        RowLayout{
            Label {
                id: v4set
                text: "I1:"
            }
            TextField{
                id: v4x
                placeholderText: "I1x"
            }

            TextField{
                id: v4y
                placeholderText: "I1y"
            }
        }
        RowLayout{
            Label {
                id: v5set
                text: "I2:"
            }
            TextField{
                id: v5x
                placeholderText: "I2x"
            }

            TextField{
                id: v5y
                placeholderText: "I2y"
            }

        }
        RowLayout{
            Label {
                id: v6set
                text: "I3:"
            }
            TextField{
                id: v6x
                placeholderText: "I3x"
            }

            TextField{
                id: v6y
                placeholderText: "I3y"
            }
        }
        RowLayout{
            CheckBox{
                id: circVis
                text: "CircleVisible"
                checked: true
            }
            CheckBox{
                id: gridVis
                text: "GridVisible"
                checked: true
            }
            Label {
                text: "Size:"
            }
            TextField{
                id: circSize
                placeholderText: "circelSize"
                text: "50"
            }
            Label {
                text: "Max U:"
            }
            TextField{
                id: maxVol
                placeholderText: "maxVoltage"
                text: "230"
            }
            Label {
                text: "Max I:"
            }
            TextField{
                id: maxCur
                placeholderText: "maxCurrent"
                text: "50"
            }
        }
    }

    StackLayout
    {
        id: stack
        currentIndex: bar.currentIndex
        anchors.top: bar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 0

        ListView {
            id: set
            anchors.fill: parent
            model: setModel
        }

        PhasorDiagram {
            anchors.fill: parent
            // anchors.topMargin: root.topMargin

            fromX: Math.floor(width/2)
            fromY: Math.floor(height/2)

            vector1Color: "red"
            vector2Color: "green"
            vector3Color: "blue"
            vector4Color: "red"
            vector5Color: "green"
            vector6Color: "blue"

            vector1Data: [v1x.text,v1y.text];
            vector2Data: [v2x.text,v2y.text];
            vector3Data: [v3x.text,v3y.text];
            vector4Data: [v4x.text,v4y.text];
            vector5Data: [v5x.text,v5y.text];
            vector6Data: [v6x.text,v6y.text];

            vector1Label: "U1";
            vector2Label: "U2";
            vector3Label: "U3";
            vector4Label: "I1";
            vector5Label: "I2";
            vector6Label: "I3";

            phiOrigin: 0
            maxVoltage: maxVol.text
            maxCurrent: maxCur.text

            circleColor: "gray"
            circleValue: circSize.text;
            circleVisible: circVis.checked;

            gridColor: "gray";
            gridVisible: gridVis.checked

            gridScale: Math.min(height,width)/maxVoltage/2

            vectorView: PhasorDiagram.VIEW_THREE_PHASE
        }

    }
    Item {
        id: notWindow
        anchors.top: parent.top
        width: parent.width
        height: parent.height-45
    }
}


