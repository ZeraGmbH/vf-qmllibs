#ifndef VECTORSETTINGSLENGTHS_H
#define VECTORSETTINGSLENGTHS_H

#include <QPainter>

class VectorSettingsLengths
{
public:
    void setNomVoltage(float nomVoltage);
    void setMinVoltage(float minVoltage);

    void setNomCurrent(float nomCurrent);
    void setMinCurrent(float minCurrent);

    void setMaxOvershoot(float maxOvershoot);

    float getNominalUOrI(int vectorIdx) const;
    float getMinimalUOrI(int vectorIdx) const;
    float getVectorLenNominalInPixels(const QPainter *painter) const;
private:
    float m_nomVoltage = 1e-9;
    float m_minVoltage = 1e-9;
    float m_nomCurrent = 1e-9;
    float m_minCurrent = 1e-9;
    float m_maxOvershoot = 1.0;
};

#endif // VECTORSETTINGSLENGTHS_H
