#include "uivectorgraphics.h"
#include <QCoreApplication>
#include <QtQml/QtQml>

void UiVectorgraphics::init()
{
    UiVectorgraphics* obj= new UiVectorgraphics();
    obj->registerTypes("uivectorgraphics");
}



void UiVectorgraphics::registerTypes(const char* uri) {
    qmlRegisterType<PhasorDiagram>(uri, 1, 0, "PhasorDiagram");
}


static void init(){
    UiVectorgraphics::init();
}
Q_COREAPP_STARTUP_FUNCTION(init)
