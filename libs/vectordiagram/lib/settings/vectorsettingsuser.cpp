#include "vectorsettingsuser.h"

void VectorSettingsUser::setVectorStandard(VectorStandard vectorStandard)
{
    m_vectorStandard = vectorStandard;
}

VectorSettingsUser::VectorStandard VectorSettingsUser::getVectorStandard() const
{
    return m_vectorStandard;
}

void VectorSettingsUser::setVectorType(VectorType vectorType)
{
    m_vectorType = vectorType;
}

VectorSettingsUser::VectorType VectorSettingsUser::getVectorType() const
{
    return m_vectorType;
}
