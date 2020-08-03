import QtQuick 2.0
import ZeraComponentsConfig 1.0
import QmlHelpersConfig 1.0

// adjust validator to locale selected
DoubleValidator {
  locale: QHC.localeName
}
