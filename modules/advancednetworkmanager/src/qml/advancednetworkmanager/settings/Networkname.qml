import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import networksettings 1.0

import "qrc:/src/qml/network"

import "qrc:/src/qml/FontAwesome.js" as FontAwesome

Pane {
    id: rootItm
    property WifiWrapper backend
    readonly property real tfratio: 1.9
    property int fontPixelSize
    Layout.minimumHeight: contentHeight
    Layout.minimumWidth: contentWidth
    padding: 0

    FontLoader {
        source: "qrc:../3rdparty/font-awesome-4.6.1/fonts/fontawesome-webfont.ttf"
    }

    GridLayout{
        id: clayout
        anchors.fill: parent
        columns: 1

        RadioButton {
            id: aprb

            text: qsTr("ACCESS POINT")
            font.pixelSize: rootItm.fontPixelSize
            checked: {
                if(backend.operationMode === WifiWrapper.Hotspot){
                    return true;
                }else{
                    return false;
                }
            }

            onClicked: {
                backend.operationMode = WifiWrapper.Hotspot;
            }

        }


        Grid{
            id: indentation
            columns: 2
            Layout.fillWidth: true

            Item{
                id: spacer
                width: parent.width/8
                height:1
            }

            GridLayout{
                width: parent.width-spacer.width-10
                columnSpacing :2
                rowSpacing :2
                Layout.margins: 0
                columns:3

                Label {
                    id: ssidLabel
                    text: qsTr("SSID")+":"
                    font.pixelSize: rootItm.fontPixelSize
                    verticalAlignment: Text.AlignVCenter
                    //Layout.fillHeight: true
                    //                Layout.fillWidth: true
                }
                TextField {
                    id: ipv4
                    readOnly: !aprb.checked
                    Layout.fillWidth: true
                    //Layout.fillHeight: true
                    font.pixelSize: rootItm.fontPixelSize
                    text: backend.apName;
                    Layout.minimumHeight: rootItm.tfratio*contentHeight
                    Layout.columnSpan: 2
                    onEditingFinished: {
                        backend.apName = text;
                    }
                }

                Label {
                    id: pwLabel
                    text: qsTr("PASSWORD")+":"
                    font.pixelSize: rootItm.fontPixelSize
                    verticalAlignment: Text.AlignVCenter
                }
                TextField {
                    id: pw
                    Layout.fillWidth: true
                    readOnly: !aprb.checked
                    font.pixelSize: rootItm.fontPixelSize
                    text: backend.apPassword;
                    Layout.minimumHeight: rootItm.tfratio*contentHeight
                    echoMode: TextInput.Password
                    onEditingFinished: {
                        backend.apPassword = text;
                    }
                }
                Button{
                    id: pwvisible
                    text: FontAwesome.icon(FontAwesome.fa_eye_slash,null)
                    font.pixelSize: rootItm.fontPixelSize
                    background: Rectangle{
                        color: "transparent"
                    }

                    onPressed: {
                        pw.echoMode = TextInput.Normal
                        pwvisible.text= FontAwesome.icon(FontAwesome.fa_eye,null)
                    }
                    onReleased: {
                        pw.echoMode = TextInput.Password
                        pwvisible.text= FontAwesome.icon(FontAwesome.fa_eye_slash,null)
                    }
                }
            }
        }
    }

}
