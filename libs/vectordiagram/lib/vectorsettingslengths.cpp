#include "vectorsettingslengths.h"
#include "vectorsettingsstatic.h"

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

float VectorSettingsLengths::getNominalUOrI(int vectorIdx) const
{
    if (vectorIdx < VectorSettingsStatic::COUNT_PHASES)
        return m_nomVoltage;
    return m_nomCurrent;
}

float VectorSettingsLengths::getMinimalUOrI(int vectorIdx) const
{
    if (vectorIdx < VectorSettingsStatic::COUNT_PHASES)
        return m_minVoltage;
    return m_minCurrent;
}

float VectorSettingsLengths::getVectorLenNominalInPixels(const QPainter *painter) const
{
    return VectorSettingsStatic::getVectorLenMaxInPixels(painter) / m_maxOvershoot;
}
