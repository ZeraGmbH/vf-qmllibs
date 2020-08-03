import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import ZeraComponentsConfig 1.0

Button {
  id: root

  // Button has special ideas - force our margins
  background.anchors.fill: root
  background.anchors.topMargin: ZCC.standardMargin
  background.anchors.bottomMargin: ZCC.standardMargin
  background.anchors.rightMargin: ZCC.standardMargin
}
