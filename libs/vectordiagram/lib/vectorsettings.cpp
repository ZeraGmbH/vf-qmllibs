#include "vectorsettings.h"
#include "vectorsettingsstatic.h"

void VectorSettings::setNomVoltage(float nomVoltage)
{
    m_nomVoltage = nomVoltage;
}

void VectorSettings::setMinVoltage(float minVoltage)
{
    m_minVoltage = minVoltage;
}

void VectorSettings::setNomCurrent(float nomCurrent)
{
    m_nomCurrent = nomCurrent;
}

void VectorSettings::setMinCurrent(float minCurrent)
{
    m_minCurrent = minCurrent;
}

void VectorSettings::setMaxOvershoot(float maxOvershoot)
{
    m_maxOvershoot = maxOvershoot;
}

float VectorSettings::getNominalUOrI(int vectorIdx) const
{
    if (vectorIdx < VectorSettingsStatic::COUNT_PHASES)
        return m_nomVoltage;
    return m_nomCurrent;
}

float VectorSettings::getMinimalUOrI(int vectorIdx) const
{
    if (vectorIdx < VectorSettingsStatic::COUNT_PHASES)
        return m_minVoltage;
    return m_minCurrent;
}

float VectorSettings::getVectorLenNominalInPixels(const QPainter *painter) const
{
    return VectorSettingsStatic::getVectorLenMaxInPixels(painter) / m_maxOvershoot;
}
