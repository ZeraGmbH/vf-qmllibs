#include "vectorsettingslayout.h"
#include "vectorpaintcalc.h"

VectorSettingsLayout::VectorStyle VectorSettingsLayout::getVectorStyle() const
{
    return m_vectorStyle;
}

void VectorSettingsLayout::setVectorStyle(VectorStyle vectorStyle)
{
    // This is a 'dummy' convenicence property. It applies multiple changes
    // on properties in here. This is fine ATTOW but as soon as QML (or other)
    // interfaces are extended to export e.g vectorLineWidthI it needs a
    // signalling mechanism when calling setVectorStyle
    m_vectorStyle = vectorStyle;

    if (m_vectorStyle == VectorStyle::ZENUX) {
        setVectorLineWidthU(0.005);
        setVectorLineWidthI(0.005);
        setArrowHeightI(0.03);
        setArrowSpreadAngleDegI(22.5);
        setLabelCollisionAvoidance(true);
    }
    else {
        setVectorLineWidthU(0.0075);
        setVectorLineWidthI(0.0125);
        setArrowHeightI(0.033);
        setArrowSpreadAngleDegI(30);
        setLabelCollisionAvoidance(true);
    }
}

QColor VectorSettingsLayout::getCoordCrossColor() const
{
    return m_coordCrossColor;
}

void VectorSettingsLayout::setCoordCrossColor(QColor coordCrossColor)
{
    m_coordCrossColor = coordCrossColor;
}

QColor VectorSettingsLayout::getCircleColor() const
{
    return m_circleColor;
}

void VectorSettingsLayout::setCircleColor(QColor circleColor)
{
    m_circleColor = circleColor;
}

bool VectorSettingsLayout::getCoordCrossVisible() const
{
    return m_coordCrossVisible;
}

void VectorSettingsLayout::setCoordCrossVisible(bool coordCrossVisible)
{
    m_coordCrossVisible = coordCrossVisible;
}

bool VectorSettingsLayout::getCircleVisible() const
{
    return m_circleVisible;
}

void VectorSettingsLayout::setCircleVisible(bool circleVisible)
{
    m_circleVisible = circleVisible;
}

float VectorSettingsLayout::getCoordCrossAndCircleLineWidth() const
{
    return m_coordCrossAndCircleLineWidth;
}

void VectorSettingsLayout::setCoordCrossAndCircleLineWidth(float coordCrossAndCircleLineWidth)
{
    m_coordCrossAndCircleLineWidth = coordCrossAndCircleLineWidth;
}

float VectorSettingsLayout::getCoordCrossAndCircleLineWidthPix(const QPainter *painter) const
{
    return VectorPaintCalc::getClipSquareLen(painter) * m_coordCrossAndCircleLineWidth;
}

float VectorSettingsLayout::getCenterDotDiameterPix(const QPainter *painter) const
{
    // Use m_vectorLineWidth
    return VectorPaintCalc::getClipSquareLen(painter) * std::max(m_vectorLineWidthU, m_vectorLineWidthI);
}

float VectorSettingsLayout::getVectorLineWidthU() const
{
    return m_vectorLineWidthU;
}

void VectorSettingsLayout::setVectorLineWidthU(float vectorLineWidth)
{
    m_vectorLineWidthU = limitLineWidth(vectorLineWidth);
}

float VectorSettingsLayout::getVectorLineWidthI() const
{
    return m_vectorLineWidthI;
}

void VectorSettingsLayout::setVectorLineWidthI(float vectorLineWidth)
{
    m_vectorLineWidthI = limitLineWidth(vectorLineWidth);
}

float VectorSettingsLayout::getVectorLineWidthPix(const QPainter *painter, PhaseType phaseType) const
{
    return VectorPaintCalc::getClipSquareLen(painter) *
           (phaseType==PhaseType::TYPE_U ? m_vectorLineWidthU : m_vectorLineWidthI);
}

float VectorSettingsLayout::getArrowHeightU() const
{
    return m_arrowHeightU;
}

void VectorSettingsLayout::setArrowHeightU(float arrowHeight)
{
    m_arrowHeightU = limitArrowHeight(arrowHeight);
}

float VectorSettingsLayout::getArrowHeightI() const
{
    return m_arrowHeightI;
}

void VectorSettingsLayout::setArrowHeightI(float arrowHeight)
{
    m_arrowHeightI = limitArrowHeight(arrowHeight);
}

float VectorSettingsLayout::getArrowHeightPix(const QPainter *painter, PhaseType phaseType) const
{
    return VectorPaintCalc::getClipSquareLen(painter) *
           (phaseType==PhaseType::TYPE_U ? m_arrowHeightU : m_arrowHeightI);
}

float VectorSettingsLayout::getArrowSpreadAngleDegU() const
{
    return m_arrowSpreadAngleDegU;
}

void VectorSettingsLayout::setArrowSpreadAngleDegU(float arrowSpreadAngle)
{
    m_arrowSpreadAngleDegU = limitArrowSpreadAngle(arrowSpreadAngle);
}

float VectorSettingsLayout::getArrowSpreadAngleDegI() const
{
    return m_arrowSpreadAngleDegI;
}

void VectorSettingsLayout::setArrowSpreadAngleDegI(float arrowSpreadAngle)
{
    m_arrowSpreadAngleDegI = limitArrowSpreadAngle(arrowSpreadAngle);
}

float VectorSettingsLayout::getArrowSpreadAngle(PhaseType phaseType) const
{
    return degToRad(phaseType==PhaseType::TYPE_U ? m_arrowSpreadAngleDegU : m_arrowSpreadAngleDegI);
}

bool VectorSettingsLayout::getLabelCollisionAvoidance() const
{
    return m_labelCollisionAvoidance;
}

void VectorSettingsLayout::setLabelCollisionAvoidance(bool collisionAvoidance)
{
    m_labelCollisionAvoidance = collisionAvoidance;
}

float VectorSettingsLayout::getLabelVectorOvershootFactor() const
{
    return m_labelVectorOvershootFactor;
}

void VectorSettingsLayout::setLabelVectorOvershootFactor(float labelVectorOvershootFactor)
{
    m_labelVectorOvershootFactor = labelVectorOvershootFactor;
}

float VectorSettingsLayout::getLabelFontSize() const
{
    return m_labelFontSize;
}

void VectorSettingsLayout::setLabelFontSize(float labelFontSize)
{
    m_labelFontSize = limitFontSize(labelFontSize);
}

QFont VectorSettingsLayout::getLabelFont(const QPainter *painter) const
{
    QFont defaultFont;
    defaultFont.setPointSizeF(VectorPaintCalc::getClipSquareLen(painter) * m_labelFontSize);
    defaultFont.setFamily("Sans");
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    defaultFont.setWeight(QFont::Medium);
#else
    defaultFont.setWeight(QFont::Weight(570)); // Mimic Qt5
#endif
    defaultFont.setKerning(false);
    return defaultFont;
}

float VectorSettingsLayout::limitArrowHeight(const float value)
{
    float limValue = value;
    constexpr float minValue = 0.0;
    if(value < minValue) {
        qWarning("Arrow height %f is too small - limit to %f", value, minValue);
        limValue = minValue;
    }
    constexpr float maxValue = 0.25;
    if(value > maxValue) {
        qWarning("Arrow height %f is too large - limit to %f", value, maxValue);
        limValue = maxValue;
    }
    return limValue;
}

float VectorSettingsLayout::limitArrowSpreadAngle(const float value)
{
    float limValue = value;
    constexpr float minValue = 5;
    if(value < minValue) {
        qWarning("Arrow spread angle %f is too small - limit to %f", value, minValue);
        limValue = minValue;
    }
    constexpr float maxValue = 60;
    if(value > maxValue) {
        qWarning("Arrow spread angle %f is too large - limit to %f", value, maxValue);
        limValue = maxValue;
    }
    return limValue;
}

float VectorSettingsLayout::limitLineWidth(const float value)
{
    float limValue = value;
    constexpr float minValue = 0;
    if(value < minValue) {
        qWarning("Line width %f is too small - limit to %f", value, minValue);
        limValue = minValue;
    }
    constexpr float maxValue = 0.1;
    if(value > maxValue) {
        qWarning("Line width %f is too large - limit to %f", value, maxValue);
        limValue = maxValue;
    }
    return limValue;
}

float VectorSettingsLayout::limitFontSize(const float value)
{
    float limValue = value;
    constexpr float minValue = 0.015;
    if(value < minValue) {
        qWarning("Font size %f is too small - limit to %f", value, minValue);
        limValue = minValue;
    }
    constexpr float maxValue = 0.1;
    if(value > maxValue) {
        qWarning("Font size %f is too large - limit to %f", value, maxValue);
        limValue = maxValue;
    }
    return limValue;
}

