#include "vectorsettingslengths.h"

void VectorSettingsLengths::setNomVoltage(float nomVoltage)
{
    m_nomVoltage = nomVoltage;
}

void VectorSettingsLengths::setMinVoltage(float minVoltage)
{
    m_minVoltage = minVoltage;
}

void VectorSettingsLengths::setNomCurrent(float nomCurrent)
{
    m_nomCurrent = nomCurrent;
}

void VectorSettingsLengths::setMinCurrent(float minCurrent)
{
    m_minCurrent = minCurrent;
}

void VectorSettingsLengths::setMaxOvershoot(float maxOvershoot)
{
    m_maxOvershoot = maxOvershoot;
}

float VectorSettingsLengths::getNominalValue(VectorSettingsStatic::VectorType vectorType) const
{
    if (vectorType == VectorSettingsStatic::TYPE_U)
        return m_nomVoltage;
    return m_nomCurrent;
}

float VectorSettingsLengths::getMinimalValue(VectorSettingsStatic::VectorType vectorType) const
{
    if (vectorType == VectorSettingsStatic::TYPE_U)
        return m_minVoltage;
    return m_minCurrent;
}

float VectorSettingsLengths::getVectorLenNominalInPixels(const QPainter *painter) const
{
    return VectorSettingsStatic::getVectorLenMaxInPixels(painter) / m_maxOvershoot;
}
