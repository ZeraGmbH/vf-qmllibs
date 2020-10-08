pragma Singleton
import QtQuick 2.0

// Container with defaults for all settings ZeraHelpers uses. To make changes
// or make settings persistent, bind them to other properties or set them on
// change
Item {
    // the single localeName property
    property string localeName: "en_GB"

    // convenient getters
    function getLocale() {
        if(!_locale_) {
            _locale_ = Qt.locale(localeName)
        }
        return _locale_
    }
    function getDecimalPoint() {
        return getLocale().decimalPoint
    }

    // internal helpers
    property var _locale_
    onLocaleNameChanged: {
        _locale_ = Qt.locale(localeName)
    }

    // Locale -> C string conversions
    function strToCLocale(str, isNumeric, isDouble) {
      if(isNumeric) {
        if(!isDouble) {
          str = String(parseInt(str, 10))
        }
        else {
          str = String(parseFloat(str.replace(",", ".")))
        }
      }
      return str
    }
    // Convert numeric string to current locale
    function strToLocal(str, isNumeric, isDouble) {
      if(isNumeric) {
        if(!isDouble) {
          str = String(parseInt(str, 10))
        }
        else {
          str = String(parseFloat(str)).replace(getDecimalPoint() === "," ? "." : ",", getDecimalPoint())
        }
      }
      return str
    }

}
