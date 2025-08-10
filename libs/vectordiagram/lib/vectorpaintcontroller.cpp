#include "vectorpaintcontroller.h"
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

    if (m_coordCrossVisible)
        VectorPrimitivesPainter::drawCoordCross(painter, m_coordCrossColor);

    if(m_circleVisible)
        VectorPrimitivesPainter::drawCircle(painter, m_settingsGeometry.m_lengths, m_circleColor);

    for(int idx=0; idx<VectorSettingsStatic::COUNT_VECTORS; ++idx) {
        if (m_vector[idx].length() > m_settingsGeometry.m_lengths.getMinimalUOrI(idx)) {
            const float nomValue = m_settingsGeometry.m_lengths.getNominalUOrI(idx);
            VectorPrimitivesPainter::drawVector(painter, m_settingsGeometry,
                                                nomValue, {m_vector[idx], m_vectorColor[idx]});
        }
    }
}
