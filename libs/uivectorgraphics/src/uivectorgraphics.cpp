#include "uivectorgraphics.h"
#include "view/phasordiagram.h"
#include <QtQml>

bool UiVectorgraphics::m_wasRegistered = false;

void UiVectorgraphics::registerQml()
{
    if(!m_wasRegistered) {
        registerTypes("uivectorgraphics");
        m_wasRegistered = true;
    }
}

void UiVectorgraphics::registerTypes(const char* uri) {
    qmlRegisterType<PhasorDiagram>(uri, 1, 0, "PhasorDiagram");
}
