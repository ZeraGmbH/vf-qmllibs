#ifndef VECTORSETTINGSLAYOUT_H
#define VECTORSETTINGSLAYOUT_H

#include <QPainter>
#include <QFont>

class VectorSettingsLayout
{
public:
    float getLabelVectorOvershootFactor();
    QFont getDefaultFont(const QPainter *painter);
private:
    float m_labelFontSize = 0.03;
    float m_labelVectorOvershootFactor = 1.07;
};

#endif // VECTORSETTINGSLAYOUT_H
