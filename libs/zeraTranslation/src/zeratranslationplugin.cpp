#include "zeratranslationplugin.h"
#include "zeratranslation.h"
#include <QCoreApplication>
#include <QtQml/QtQml>

void ZeraTranslationPlugin::init()
{
    ZeraTranslationPlugin* obj= new ZeraTranslationPlugin();
    obj->registerTypes("ZeraTranslation");
}



void ZeraTranslationPlugin::registerTypes(const char* uri) {
    ZeraTranslation* zeraTranslation=ZeraTranslation::getInstance();
    zeraTranslation->changeLanguage("C");
    // Register internal worker not intended for external use
    qmlRegisterSingletonType<ZeraTranslation>(QString().append(uri).append("backend").toLatin1(), 1, 0, "ZTR", ZeraTranslation::getStaticInstance);
    // Register our magic Z.tr("<text-to-translate>")
    qmlRegisterSingletonType(QUrl("qrc:/src/qml/TranslationHelper.qml"), uri, 1, 0, "Z");
}


static void init(){
    ZeraTranslationPlugin::init();
}
Q_COREAPP_STARTUP_FUNCTION(init)
