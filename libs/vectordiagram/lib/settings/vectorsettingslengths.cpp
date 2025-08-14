#include "vectorsettingslengths.h"
#include "vectorpaintcalc.h"

VectorSettingsLengths::VectorNominals VectorSettingsLengths::getNominalSelection() const
{
    return m_nominalSelection;
}

void VectorSettingsLengths::setNominalSelection(VectorNominals nominalSelection)
{
    m_nominalSelection = nominalSelection;
}

float VectorSettingsLengths::getNomVoltage() const
{
    return m_nomVoltage;
}

void VectorSettingsLengths::setNomVoltage(float nomVoltage)
{
    m_nomVoltage = nomVoltage;
}

float VectorSettingsLengths::getNomCurrent() const
{
    return m_nomCurrent;
}

void VectorSettingsLengths::setNomCurrent(float nomCurrent)
{
    m_nomCurrent = nomCurrent;
}

float VectorSettingsLengths::getMinVoltage() const
{
    return m_minVoltage;
}

void VectorSettingsLengths::setMinVoltage(float minVoltage)
{
    m_minVoltage = minVoltage;
}

float VectorSettingsLengths::getMinCurrent() const
{
    return m_minCurrent;
}

void VectorSettingsLengths::setMinCurrent(float minCurrent)
{
    m_minCurrent = minCurrent;
}

float VectorSettingsLengths::getMaxVoltage() const
{
    return m_maxVoltage;
}

float VectorSettingsLengths::getMaxCurrent() const
{
    return m_maxCurrent;
}

float VectorSettingsLengths::getMaxOvershootFactor() const
{
    return m_maxOvershoot;
}

void VectorSettingsLengths::setMaxOvershootFactor(float maxOvershoot)
{
    m_maxOvershoot = maxOvershoot;
}

void VectorSettingsLengths::setMaxU(float maxU)
{
    m_maxVoltage = maxU;
}

void VectorSettingsLengths::setMaxI(float maxI)
{
    m_maxCurrent = maxI;
}

float VectorSettingsLengths::getNomOrMaxValue(PhaseType phaseType) const
{
    if (phaseType == PhaseType::TYPE_U)
        return m_nominalSelection == VectorNominals::NOMINAL ? m_nomVoltage: m_maxVoltage;
    return m_nominalSelection == VectorNominals::NOMINAL ? m_nomCurrent : m_maxCurrent;
}

float VectorSettingsLengths::getMinimalValue(PhaseType phaseType) const
{
    if (phaseType == PhaseType::TYPE_U)
        return m_minVoltage;
    return m_minCurrent;
}

float VectorSettingsLengths::getVectorLenNominalInPixels(const QPainter *painter) const
{
    constexpr float totalLenAvail = 1.0;
    constexpr float extraLabelLenFromAvail = 0.18;
    constexpr float vectorLenFromAvail = totalLenAvail - extraLabelLenFromAvail;
    const float pixelsAvailforVector = VectorPaintCalc::getClipSquareLen(painter) / 2 * vectorLenFromAvail;

    return pixelsAvailforVector / m_maxOvershoot;
}
