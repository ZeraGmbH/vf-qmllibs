#include "vectorpaintcontroller.h"
#include "vectorpaintcalc.h"
#include "vectorprimitivespainter.h"
#include <QMultiMap>
#include <math.h>

void VectorPaintController::setVectorStandard(VectorStandard vectorStandard)
{
    m_vectorStandard = vectorStandard;
}

VectorPaintController::VectorStandard VectorPaintController::getVectorStandard() const
{
    return m_vectorStandard;
}

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

    adjustAngleSettings();

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

void VectorPaintController::adjustAngleSettings()
{
    switch(m_vectorStandard) {
    case VectorStandard::DIN: {
        const float angleUL1 = atan2(m_vector[0].y(), m_vector[0].x());
        m_vectorSettings.m_angles.setRotationDirection(VectorSettingsAngles::Clockwise);
        m_vectorSettings.m_angles.setOffsetAngle(angleUL1-degToRad(90));
        break;
    }
    case VectorStandard::IEC: {
        const float angleIL1 = atan2(m_vector[VectorSettingsStatic::COUNT_PHASES].y(), m_vector[VectorSettingsStatic::COUNT_PHASES].x());
        // Interesting: We expected VectorSettingsAngles::Mathematical but that is true
        // onlx if angle passed in are in IEC sytyle to. We come in as DIN always
        m_vectorSettings.m_angles.setRotationDirection(VectorSettingsAngles::Clockwise);
        m_vectorSettings.m_angles.setOffsetAngle(-angleIL1);
        break;
    }
    case VectorStandard::ANSI: {
        const float angleUL1 = atan2(m_vector[0].y(), m_vector[0].x());
        m_vectorSettings.m_angles.setRotationDirection(VectorSettingsAngles::Clockwise);
        m_vectorSettings.m_angles.setOffsetAngle(angleUL1);
        break;
    }
    }
}
