#ifndef VECTORSETTINGSLENGTHS_H
#define VECTORSETTINGSLENGTHS_H

#include "vectorsettingsstatic.h"
#include <QPainter>

class VectorSettingsLengths
{
public:
    void setNomVoltage(float nomVoltage);
    void setMinVoltage(float minVoltage);

    void setNomCurrent(float nomCurrent);
    void setMinCurrent(float minCurrent);

    float getMaxOvershootFactor() const;
    void setMaxOvershootFactor(float maxOvershoot);

    float getNominalValue(VectorSettingsStatic::VectorType vectorType) const;
    float getMinimalValue(VectorSettingsStatic::VectorType vectorType) const;
    float getVectorLenNominalInPixels(const QPainter *painter) const;
private:
    float m_nomVoltage = 1e-9;
    float m_minVoltage = 1e-9;
    float m_nomCurrent = 1e-9;
    float m_minCurrent = 1e-9;
    float m_maxOvershoot = 1.0;
};

#endif // VECTORSETTINGSLENGTHS_H
