#include "vectorpaintcontroller.h"
#include "vectorpaintcalc.h"
#include "vectorprimitivespainter.h"
#include <QMultiMap>
#include <math.h>

void VectorPaintController::setMaxOvershootFactor(float maxOvershoot)
{
    m_settingsGeometry.m_lengths.setMaxOvershoot(maxOvershoot);
}

void VectorPaintController::setNominalVoltage(float nomVoltage)
{
    m_settingsGeometry.m_lengths.setNomVoltage(nomVoltage);
}

void VectorPaintController::setMinVoltage(float minVoltage)
{
    m_settingsGeometry.m_lengths.setMinVoltage(minVoltage);
}

void VectorPaintController::setNominalCurrent(float nomCurrent)
{
    m_settingsGeometry.m_lengths.setNomCurrent(nomCurrent);
}

void VectorPaintController::setMinCurrent(float minCurrent)
{
    m_settingsGeometry.m_lengths.setMinCurrent(minCurrent);
}

void VectorPaintController::setVectorType(VectorType vectorType)
{
    m_vectorType = vectorType;
}

void VectorPaintController::setCoordCrossVisible(bool coordCrossVisible)
{
    m_coordCrossVisible = coordCrossVisible;
}

void VectorPaintController::setCoordCrossColor(const QColor &coordCrossColor)
{
    m_coordCrossColor = coordCrossColor;
}

void VectorPaintController::setCircleVisible(bool circleVisible)
{
    m_circleVisible = circleVisible;
}

void VectorPaintController::setCircleColor(const QColor &circleColor)
{
    m_circleColor = circleColor;
}

void VectorPaintController::setVector(int idx, const QVector2D &vector)
{
    m_vector[idx] = vector;
}

void VectorPaintController::setVectorColor(int idx, const QColor &vectorColor)
{
    m_vectorColor[idx] = vectorColor;
}

void VectorPaintController::setVectorLabel(int idx, const QString &vectorLabel)
{
    m_vectorLabel[idx] = vectorLabel;
}

void VectorPaintController::paint(QPainter *painter)
{
    VectorSettingsStatic::setFontForLabels(painter);

    const float coordCircleLineWidth = VectorSettingsStatic::getCoordCrossAndCircleLineWidth(painter);
    if (m_coordCrossVisible)
        VectorPrimitivesPainter::drawCoordCross(painter, m_coordCrossColor, coordCircleLineWidth);

    if(m_circleVisible)
        VectorPrimitivesPainter::drawCircle(painter, m_settingsGeometry.m_lengths, m_circleColor, coordCircleLineWidth);

    bool vectorDrawn = false;
    for(int idx=0; idx<VectorSettingsStatic::COUNT_VECTORS; ++idx) {
        VectorSettingsStatic::VectorType type = VectorSettingsStatic::getVectorType(idx);
        if (m_vector[idx].length() > m_settingsGeometry.m_lengths.getMinimalValue(type)) {
            const float lineWidth = VectorSettingsStatic::getVectorLineWidth(painter);
            QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
                painter, { m_settingsGeometry, type }, m_vector[idx]);
            VectorPrimitivesPainter::drawVector(painter, { pixLenVector, m_vectorColor[idx] }, lineWidth);
            vectorDrawn = true;
        }
    }
    if(vectorDrawn)
        VectorPrimitivesPainter::drawCoordCenterDot(painter, m_coordCrossColor, VectorSettingsStatic::getCenterDotDiameter(painter));
}
