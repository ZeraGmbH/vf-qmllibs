#ifndef VECTORSETTINGSLAYOUT_H
#define VECTORSETTINGSLAYOUT_H

#include "vectorconstants.h"
#include <QObject>
#include <QPainter>
#include <QFont>

class VectorSettingsLayout : public QObject
{
    Q_OBJECT
public:
    enum class VectorStyle : int
    {
        UNDEFINED, // no style set - use defaults from settings (e.g for tests)
        ZENUX,     // oldschoo ZENUX narrow vectors
        WEBSAM     // mimic WebSam approach wide current vectors
    };
    Q_ENUM(VectorStyle)
    VectorStyle getVectorStyle() const;
    void setVectorStyle(VectorStyle vectorStyle);

    // Below are intended to be set by tests or style selection
    // Once we allow users to set them outside of style we have
    // to implement change signalling
    QColor getCoordCrossColor() const;
    void setCoordCrossColor(QColor coordCrossColor);
    QColor getCircleColor() const;
    void setCircleColor(QColor circleColor);

    bool getCoordCrossVisible() const;
    void setCoordCrossVisible(bool coordCrossVisible);

    bool getCircleVisible() const;
    void setCircleVisible(bool circleVisible);

    float getCoordCrossAndCircleLineWidth() const;
    void setCoordCrossAndCircleLineWidth(float coordCrossAndCircleLineWidth);
    float getCoordCrossAndCircleLineWidthPix(const QPainter *painter) const;

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

    float getArrowSpreadAngleDegU() const;
    void setArrowSpreadAngleDegU(float arrowSpreadAngle);
    float getArrowSpreadAngleDegI() const;
    void setArrowSpreadAngleDegI(float arrowSpreadAngle);
    float getArrowSpreadAngle(PhaseType phaseType) const;

    bool getLabelCollisionAvoidance() const;
    void setLabelCollisionAvoidance(bool collisionAvoidance);

    float getLabelVectorOvershootFactor() const;
    void setLabelVectorOvershootFactor(float labelVectorOvershootFactor);

    float getLabelFontSize() const;
    void setLabelFontSize(float labelFontSize);
    QFont getLabelFont(const QPainter *painter) const;

private:
    static float limitArrowHeight(const float value);
    static float limitArrowSpreadAngle(const float value);
    static float limitLineWidth(const float value);
    static float limitFontSize(const float value);

    VectorStyle m_vectorStyle = VectorStyle::UNDEFINED;
    bool m_coordCrossVisible = true;
    bool m_circleVisible = true;
    float m_coordCrossAndCircleLineWidth = 0.004;
    QColor m_coordCrossColor = Qt::darkGray;
    QColor m_circleColor = Qt::darkGray;
    float m_vectorLineWidthU = 0.01;
    float m_vectorLineWidthI = 0.01;
    float m_arrowHeightU = 0.03;
    float m_arrowHeightI = 0.03;
    float m_arrowSpreadAngleDegU = 22.5;
    float m_arrowSpreadAngleDegI = 22.5;
    float m_labelFontSize = 0.03;
    float m_labelVectorOvershootFactor = 1.11;
    bool m_labelCollisionAvoidance = false;
};

#endif // VECTORSETTINGSLAYOUT_H
