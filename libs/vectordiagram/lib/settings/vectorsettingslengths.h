#ifndef VECTORSETTINGSLENGTHS_H
#define VECTORSETTINGSLENGTHS_H

#include "vectorconstants.h"
#include <QPainter>

enum class VectorNominals : int
{
    NOMINAL, // values with length == nominal value land on circle
    MAXIMUM  // values with max values land on circle (nominal values are ignored)
};

Q_DECLARE_METATYPE(VectorNominals)

class VectorSettingsLengths
{
public:
    // external
    VectorNominals getNominalSelection() const;
    void setNominalSelection(VectorNominals nominalSelection);

    float getNomVoltage() const;
    void setNomVoltage(float nomVoltage);
    float getNomCurrent() const;
    void setNomCurrent(float nomCurrent);

    float getMinVoltage() const;
    void setMinVoltage(float minVoltage);
    float getMinCurrent() const;
    void setMinCurrent(float minCurrent);

    float getMaxOvershootFactor() const;
    void setMaxOvershootFactor(float maxOvershoot);

    // internal
    void setMaxU(float maxU);
    void setMaxI(float maxI);
    float getNomOrMaxValue(PhaseType phaseType) const;
    float getMinimalValue(PhaseType phaseType) const;
    float getVectorLenNominalInPixels(const QPainter *painter) const;
private:
    VectorNominals m_nominalSelection = VectorNominals::MAXIMUM;
    float m_nomVoltage = 1e-9;
    float m_minVoltage = 1e-9;
    float m_nomCurrent = 1e-9;
    float m_minCurrent = 1e-9;
    float m_maxOvershoot = 1.0;
    float m_maxVoltage = 0.0;
    float m_maxCurrent = 0.0;
};

#endif // VECTORSETTINGSLENGTHS_H
