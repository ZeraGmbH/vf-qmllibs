#ifndef VECTORSETTINGSLAYOUT_H
#define VECTORSETTINGSLAYOUT_H

#include "vectorconstants.h"
#include <QPainter>
#include <QFont>

class VectorSettingsLayout
{
public:
    bool getCoordCrossVisible() const;
    void setCoordCrossVisible(bool coordCrossVisible);

    bool getCircleVisible() const;
    void setCircleVisible(bool circleVisible);

    float getCoordCrossAndCircleLineWidth() const;
    void setCoordCrossAndCircleLineWidth(float coordCrossAndCircleLineWidth);
    float getCoordCrossAndCircleLineWidthPix(const QPainter *painter) const;

    QColor getCoordCrossColor() const;
    void setCoordCrossColor(QColor coordCrossColor);
    QColor getCircleColor() const;
    void setCircleColor(QColor circleColor);

    float getCenterDotDiameterPix(const QPainter *painter) const;

    float getVectorLineWidthU() const;
    void setVectorLineWidthU(float vectorLineWidth);
    float getVectorLineWidthI() const;
    void setVectorLineWidthI(float vectorLineWidth);
    float getVectorLineWidthPix(const QPainter *painter, PhaseType phaseType) const;

    float getArrowHeightU() const;
    void setArrowHeightU(float arrowHeight);
    float getArrowHeightI() const;
    void setArrowHeightI(float arrowHeight);
    float getArrowHeightPix(const QPainter *painter, PhaseType phaseType) const;

    float getArrowSpreadAngleDeg() const;
    void setArrowSpreadAngleDeg(float arrowSpreadAngle);
    float getArrowSpreadAngle() const;

    float getLabelVectorOvershootFactor() const;
    void setLabelVectorOvershootFactor(float labelVectorOvershootFactor);

    float getLabelFontSize() const;
    void setLabelFontSize(float labelFontSize);
    QFont getLabelFont(const QPainter *painter) const;

private:
    bool m_coordCrossVisible = true;
    bool m_circleVisible = true;
    float m_coordCrossAndCircleLineWidth = 0.004;
    QColor m_coordCrossColor = Qt::darkGray;
    QColor m_circleColor = Qt::darkGray;
    float m_vectorLineWidthU = 0.01;
    float m_vectorLineWidthI = 0.01;
    float m_arrowHeightU = 0.03;
    float m_arrowHeightI = 0.03;
    float m_arrowSpreadAngleDeg = 22.5;
    float m_labelFontSize = 0.03;
    float m_labelVectorOvershootFactor = 1.07;
};

#endif // VECTORSETTINGSLAYOUT_H
