#include "zerafa.h"
#include <QtQml>

bool ZeraFa::m_wasRegistered = false;

void ZeraFa::registerQml()
{
    if(!m_wasRegistered) {
        registerTypes("ZeraFa");
        m_wasRegistered = true;
    }
}

void ZeraFa ::registerTypes(const char* uri) {
    Q_INIT_RESOURCE(zerafa);
    //FontAwesome Free Release 5.14.0
    qmlRegisterSingletonType(QUrl("qrc:/qml/ZeraFa514.qml"), uri, 1, 1, "FA");
    //FontAwesome Free Release unknown
    qmlRegisterSingletonType(QUrl("qrc:/qml/ZeraFaOld.qml"), uri, 1, 0, "FA");
}
