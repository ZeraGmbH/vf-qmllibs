#include "zerafa.h"
#include <QtQml>

void ZeraFa::registerQml()
{
    registerTypes("ZeraFa");
}

void ZeraFa ::registerTypes(const char* uri) {
    //FontAwesome Free Release 5.14.0
    qmlRegisterSingletonType(QUrl("qrc:/qml/ZeraFa514.qml"), uri, 1, 1, "FA");
    //FontAwesome Free Release unknown
    qmlRegisterSingletonType(QUrl("qrc:/qml/ZeraFaOld.qml"), uri, 1, 0, "FA");
}
