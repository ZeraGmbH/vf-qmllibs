#include "vectorpaintcontroller.h"
#include "vectorpaintcalc.h"
#include "vectorprimitivespainter.h"
#include <QMultiMap>
#include <math.h>

void VectorPaintController::setVectorType(VectorType vectorType)
{
    m_vectorType = vectorType;
}

VectorSettings *VectorPaintController::getVectorSettings()
{
    return &m_vectorSettings;
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
    painter->setFont(m_vectorSettings.m_layout.getLabelFont(painter));

    if(m_vectorSettings.m_layout.getCoordCrossVisible())
        VectorPrimitivesPainter::drawCoordCross(painter, m_vectorSettings.m_layout);
    if(m_vectorSettings.m_layout.getCircleVisible())
        VectorPrimitivesPainter::drawCircle(painter, m_vectorSettings.m_lengths, m_vectorSettings.m_layout);

    bool vectorDrawn = false;
    for(int idx=0; idx<VectorSettingsStatic::COUNT_VECTORS; ++idx) {
        VectorSettingsStatic::VectorType type = VectorSettingsStatic::getVectorType(idx);
        if (m_vector[idx].length() > m_vectorSettings.m_lengths.getMinimalValue(type)) {
            QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
                painter, { m_vectorSettings, type }, m_vector[idx]);
            VectorPrimitivesPainter::drawVector(painter, { pixLenVector, m_vectorColor[idx] }, m_vectorSettings.m_layout);
            VectorPrimitivesPainter::drawLabel(painter,
                                               { pixLenVector * m_vectorSettings.m_layout.getLabelVectorOvershootFactor(),
                                                m_vectorColor[idx]},
                                                m_vectorSettings.m_layout.getLabelFont(painter),
                                                m_vectorLabel[idx]);
            vectorDrawn = true;
        }
    }
    if(vectorDrawn)
        VectorPrimitivesPainter::drawCoordCenterDot(painter, m_vectorSettings.m_layout);
}
