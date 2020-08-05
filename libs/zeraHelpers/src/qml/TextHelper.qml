pragma Singleton
import QtQuick 2.0
import QmlHelpersConfig 1.0

Item {
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
  function strToLocal(str, isNumeric, isDouble) {
    if(isNumeric) {
      if(!isDouble) {
        str = String(parseInt(str, 10))
      }
      else {
        str = String(parseFloat(str)).replace(QHC.locale.decimalPoint === "," ? "." : ",", QHC.locale.decimalPoint)
      }
    }
    return str
  }
  function hasAlteredValue(isNumeric, isDouble, decimals, fieldText, text) {
    var altered = false
    // Numerical?
    if(isNumeric) {
      if(fieldText !== text && (fieldText === "" || text === "")) {
        altered = true
      }
      else if(isDouble) {
        var expVal = Math.pow(10, decimals)
        var fieldVal = parseFloat(strToCLocale(fieldText, isNumeric, isDouble)) * expVal
        var textVal = parseFloat(text) * expVal
        altered = Math.abs(fieldVal-textVal) > 0.1
      }
      else {
        altered = parseInt(fieldText, 10) !== parseInt(text, 10)
      }
    }
    else {
      altered = fieldText !== text
    }
    return altered
  }

  function hasValidInput(isDouble, text) {
    var valid = true
    if(isDouble) {
      // Sometimes wrong decimal separator is accepted by DoubleValidator so check for it
      if(QHC.locale.decimalPoint === "," ? text.includes(".") : text.includes(",")) {
        valid = false
      }
    }
    return valid
  }
}
