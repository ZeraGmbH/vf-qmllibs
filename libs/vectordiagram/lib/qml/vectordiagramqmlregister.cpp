#include "vectordiagramqmlregister.h"
#include "vectordiagramqml.h"
#include "vectorsettingsuser.h"
#include "vectorsettingslengths.h"
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
    qmlRegisterType<VectorDiagramQml>("VectorDiagramQml", 1, 0, "VectorDiagram");
    qmlRegisterType<VectorSettingsUser>("VectorDiagramQml", 1, 0, "VectorSettingsUser");
    qmlRegisterType<VectorSettingsLengths>("VectorDiagramQml", 1, 0, "VectorSettingsLengths");
}
