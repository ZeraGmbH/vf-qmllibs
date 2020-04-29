import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import QtQml 2.12
import networksettings 1.0

Pane{
    id: rootItm
    property WiredWrapper backend
    readonly property real tfratio: 1.9
    //    Layout.minimumHeight: contentHeight
    //    Layout.minimumWidth: contentWidth
    property int fontPixelSize
    padding: 0

    GridLayout{
        anchors.fill: parent
        anchors.margins: 0
        columns: 2

        RowLayout{
            Layout.margins: 0
            Layout.columnSpan: 2
            Label {
                id: ipv4Topic
                font.pixelSize: rootItm.fontPixelSize
                Layout.fillHeight: true
                verticalAlignment: Text.AlignVCenter
                text: qsTr("IPV6")
            }

            IpDetType{
                id: detT
                //Layout.fillHeight: true
                Layout.fillWidth: true
                backend: rootItm.backend
                fontPixelSize: rootItm.fontPixelSize
                ipType: "ipv6"
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
                columns:2

                Label {
                    id: ipv6Label
                    text: "IP  "
                    font.pixelSize: rootItm.fontPixelSize
                    verticalAlignment: Text.AlignVCenter
                }

                TextField {
                    id: ipv6
                    horizontalAlignment : TextInput.AlignRight
                    validator: RegExpValidator { regExp: /([a-f0-9:]+:+)+[a-f0-9]+/}
                    readOnly: {
                        if(WiredWrapper.Manual===backend.currentIpv6ConType){
                            return false;
                        }else{
                            return true;
                        }
                    }
                    Layout.fillWidth: true
                    //Layout.fillHeight: true
                    font.pixelSize: rootItm.fontPixelSize
                    text: {
                        if(focus && !readOnly){
                            return "";
                        }else{
                            return backend.ipv6;

                        }
                    }
                    Layout.minimumHeight: rootItm.tfratio*contentHeight
                    onEditingFinished: {
                        rootItm.backend.ipv6 = text;
                    }
                }
                Label {
                    id: subnetmaskLabel
                    text: "PREFIXLENGTH  "
                    font.pixelSize: rootItm.fontPixelSize
                    verticalAlignment: Text.AlignVCenter

                }
                TextField {
                    id: subnetmask
                    horizontalAlignment : TextInput.AlignRight
                    readOnly: {
                        if(WiredWrapper.Manual===backend.currentIpv6ConType){
                            return false;
                        }else{
                            return true;
                        }
                    }

                    font.pixelSize: rootItm.fontPixelSize
                    Layout.fillWidth: true
                    text: {
                        if(focus && !readOnly){
                            return "";
                        }else{
                            return backend.prefix;
                        }
                    }
                    onEditingFinished: {
                        rootItm.backend.prefix = text;
                    }

                    Layout.minimumHeight: rootItm.tfratio*contentHeight
                }


            }
        }
    }
}

