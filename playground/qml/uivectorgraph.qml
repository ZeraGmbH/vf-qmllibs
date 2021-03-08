import QtQuick 2.0

import QtQuick 2.0

import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

import uivectorgraphics 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "uivector"


    // resolution the gui was designed with
    readonly property int defWidth : 800
    readonly property int defHeight : 400

    width: 800
    height: 480


    property int count: 0



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
            text: "v1:"
        }
        TextField{
            id: v1x
            placeholderText: "v1x"
            text: "125"
        }

        TextField{
            id: v1y
            placeholderText: "v1y"
            text: "125"
        }

        }
        RowLayout{
        Label {
            id: v2set
            text: "v2:"
        }
        TextField{
            id: v2x
            placeholderText: "v2x"
        }

        TextField{
            id: v2y
            placeholderText: "v2y"
        }

        }
        RowLayout{
        Label {
            id: v3set
            text: "v3:"
        }

        TextField{
            id: v3x
            placeholderText: "v3x"
        }

        TextField{
            id: v3y
            placeholderText: "v3y"
        }



        }
        RowLayout{
        Label {
            id: v4set
            text: "i1:"
        }
        TextField{
            id: v4x
            placeholderText: "i1x"
        }

        TextField{
            id: v4y
            placeholderText: "i1y"
        }
        }
        RowLayout{
        Label {
            id: v5set
            text: "i2:"
        }
        TextField{
            id: v5x
            placeholderText: "i2x"
        }

        TextField{
            id: v5y
            placeholderText: "i2y"
        }

        }
        RowLayout{
        Label {
            id: v6set
            text: "i3:"
        }
        TextField{
            id: v6x
            placeholderText: "i3x"
        }

        TextField{
            id: v6y
            placeholderText: "i3y"
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
            TextField{
                id: circSize
                placeholderText: "circelSize"
                text: "50"
            }
            TextField{
                id: maxVol
                placeholderText: "maxVoltage"
                text: "230"
            }
            TextField{
                id: maxCur
                placeholderText: "maxCurrent"
                text: "50"
            }
        }




    }


    StackLayout
    //SwipeView
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

          vector1Label: "v1";
          vector2Label: "v2";
          vector3Label: "v3";
          vector4Label: "i1";
          vector5Label: "i2";
          vector6Label: "v3";

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
          vectorMode: PhasorDiagram.DIN410
          currentVisible: true
        }


    }

    Item {
            id: notWindow
            anchors.top: parent.top
            width: parent.width
            height: parent.height-45
        }



}


