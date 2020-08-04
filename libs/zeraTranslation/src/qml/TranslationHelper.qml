pragma Singleton

import QtQuick 2.0
import ZeraTranslationbackend 1.0

Item {


    signal languageChanged();

    id: root
    function tr(key){
        if(Array.isArray(key)){ //translating array e.g. text models
            var newkey = [];
            for(var i = 0; i < key.length; i++){
                if(ZTR[key[i]] !== undefined){
                    newkey[i] = ZTR[key[i]];
                }else{
                    newkey[i]=key[i];
                }
            }
            return newkey;
        }else{ //translating normal text elements
            if(ZTR[key] !== undefined){
                return  ZTR[key];
            }else{
                return  key;
            }
        }
    }
    function changeLanguage(language) {
        ZTR.changeLanguage(language)
    }
}
