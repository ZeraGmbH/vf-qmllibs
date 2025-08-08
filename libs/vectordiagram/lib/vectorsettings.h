#ifndef VECTORSETTINGS_H
#define VECTORSETTINGS_H

#include <QPainter>

class VectorSettings
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
    float m_nomVoltage = 0.0;
    float m_minVoltage = 0.0;
    float m_nomCurrent = 0.0;
    float m_minCurrent = 0.0;
    float m_maxOvershoot = 1.25;
};

#endif // VECTORSETTINGS_H
