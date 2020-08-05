import QtQuick 2.0
import ZeraComponentsConfig 1.0
import ZeraLocale 1.0

// adjust validator to locale selected
DoubleValidator {
    // A bit confusing but yes it is the localeName here
    locale: ZLocale.localeName
}
