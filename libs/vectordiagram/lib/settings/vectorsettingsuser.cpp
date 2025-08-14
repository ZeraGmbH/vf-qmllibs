#include "vectorsettingsuser.h"

void VectorSettingsUser::setVectorStandard(VectorStandard vectorStandard)
{
    m_vectorStandard = vectorStandard;
}

VectorStandard VectorSettingsUser::getVectorStandard() const
{
    return m_vectorStandard;
}

void VectorSettingsUser::setVectorType(VectorType vectorType)
{
    m_vectorType = vectorType;
}

VectorType VectorSettingsUser::getVectorType() const
{
    return m_vectorType;
}
