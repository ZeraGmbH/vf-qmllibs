#include "zeracomponents.h"
#include <QCoreApplication>
#include <QtQml/QtQml>

void ZeraComponents::init()
{
    ZeraComponents* obj= new ZeraComponents();
    obj->registerTypes("ZeraComponents");
}

void ZeraComponents::registerTypes(const char* uri) {

}

static void init(){
    ZeraComponents::init();
}
Q_COREAPP_STARTUP_FUNCTION(init)
