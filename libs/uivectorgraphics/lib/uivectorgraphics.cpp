#include "uivectorgraphics.h"
#include "view/phasordiagram.h"
#include <QtQml>

bool UiVectorgraphics::m_wasRegistered = false;

void UiVectorgraphics::registerQml()
{
    if(!m_wasRegistered) {
        registerTypes();
        m_wasRegistered = true;
    }
}

void UiVectorgraphics::registerTypes()
{
    qmlRegisterType<PhasorDiagram>("uivectorgraphics", 1, 0, "PhasorDiagram");
}
