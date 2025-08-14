#include "vectordiagramqmlregister.h"
#include "vectordiagramqml.h"
#include <QQmlEngine>

bool VectorDiagramQmlRegister::m_wasRegistered = false;

void VectorDiagramQmlRegister::registerQml()
{
    if(!m_wasRegistered) {
        registerTypes();
        m_wasRegistered = true;
    }
}

void VectorDiagramQmlRegister::registerTypes()
{
    qmlRegisterType<VectorDiagramQml>("VectorDiagram", 1, 0, "VectorDiagram");
}
