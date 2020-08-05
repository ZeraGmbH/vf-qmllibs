#ifndef ZERATRANSLATIONPLUGIN_H
#define ZERATRANSLATIONPLUGIN_H

#include <QtQml/QQmlExtensionPlugin>

class ZeraTranslationPlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "zeratranslation/1.0")

public:
    /**
     * @brief init library
     *
     * This function will init the library and
     * register the c++ classes.
     * It is automaticly called by QT if the library is linked.
     *
     */
    static void init();
    /**
     * @brief registerTypes Overrided function that should register all
     * C++ classes exported by this plugin.
     * @param uri           Plugin uri.
     */
    void registerTypes(const char* uri) override;
};

#endif // ZERATRANSLATIONPLUGIN_H
