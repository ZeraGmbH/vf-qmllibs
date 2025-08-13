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

VectorPaintController::VectorType VectorPaintController::getVectorType() const
{
    return m_vectorType;
}

VectorSettings *VectorPaintController::getVectorSettings()
{
    return &m_vectorSettings;
}

void VectorPaintController::setVector(int idx, const QVector2D &vector)
{
    m_inVectors[idx] = vector;
}

void VectorPaintController::setVectorColor(int idx, const QColor &vectorColor)
{
    m_inVectorColors[idx] = vectorColor;
}

void VectorPaintController::setVectorLabel(int idx, const QString &vectorLabel)
{
    m_inVectorLabels[idx] = vectorLabel;
}

void VectorPaintController::paint(QPainter *painter)
{
    painter->setFont(m_vectorSettings.m_layout.getLabelFont(painter));

    if(m_vectorSettings.m_layout.getCoordCrossVisible())
        VectorPrimitivesPainter::drawCoordCross(painter, m_vectorSettings.m_layout);
    if(m_vectorSettings.m_layout.getCircleVisible())
        VectorPrimitivesPainter::drawCircle(painter, m_vectorSettings.m_lengths, m_vectorSettings.m_layout);

    VectorDataCurrent currentData = {m_inVectorColors, m_inVectorLabels, m_inVectors};
    if (getVectorType() == VectorType::VIEW_THREE_PHASE)
        currentData = calc3WireVectorData(currentData);

    adjustAngleSettings(currentData);

    bool vectorDrawn = false;
    switch (getVectorType()) {
    case VectorType::VIEW_STAR:
        if (drawVoltageStar(painter, currentData))
            vectorDrawn = true;
        if (drawCurrentStar(painter, currentData))
            vectorDrawn = true;
        break;
    case VectorType::VIEW_TRIANGLE:
        drawVoltageTriangle(painter, currentData);
        if (drawCurrentStar(painter, currentData))
            vectorDrawn = true;
        break;
    case VectorType::VIEW_THREE_PHASE:
        if (drawVoltageStar(painter, currentData))
            vectorDrawn = true;
        if (drawCurrentStar(painter, currentData))
            vectorDrawn = true;
        break;
    }
    drawLabels(painter, currentData);
    if(vectorDrawn)
        VectorPrimitivesPainter::drawCoordCenterDot(painter, m_vectorSettings.m_layout);
}

void VectorPaintController::adjustAngleSettings(const VectorDataCurrent& currentVectors)
{
    switch(m_vectorStandard) {
    case VectorStandard::DIN: {
        const float angleUL1 = atan2(currentVectors.m_vectorData[VectorSettingsStatic::IDX_UL1].y(),
                                     currentVectors.m_vectorData[VectorSettingsStatic::IDX_UL1].x());
        m_vectorSettings.m_angles.setRotationDirection(VectorSettingsAngles::Clockwise);
        m_vectorSettings.m_angles.setOffsetAngle(-degToRad(90)-angleUL1);
        break;
    }
    case VectorStandard::IEC: {
        const float angleIL1 = atan2(currentVectors.m_vectorData[VectorSettingsStatic::IDX_IL1].y(),
                                     currentVectors.m_vectorData[VectorSettingsStatic::IDX_IL1].x());
        // Interesting: We expected VectorSettingsAngles::Mathematical but that is true
        // only if angle passed in are in IEC sytyle to. We come in as DIN always
        m_vectorSettings.m_angles.setRotationDirection(VectorSettingsAngles::Clockwise);
        m_vectorSettings.m_angles.setOffsetAngle(-angleIL1);
        break;
    }
    case VectorStandard::ANSI: {
        const float angleUL1 = atan2(currentVectors.m_vectorData[VectorSettingsStatic::IDX_UL1].y(),
                                     currentVectors.m_vectorData[VectorSettingsStatic::IDX_UL1].x());
        m_vectorSettings.m_angles.setRotationDirection(VectorSettingsAngles::Clockwise);
        m_vectorSettings.m_angles.setOffsetAngle(angleUL1);
        break;
    }
    }
}

bool VectorPaintController::drawVoltageStar(QPainter *painter, const VectorDataCurrent &currentVectors)
{
    return drawPhasesStar(painter, VectorSettingsStatic::IDX_UL1, VectorSettingsStatic::IDX_UL3, currentVectors);
}

bool VectorPaintController::drawCurrentStar(QPainter *painter, const VectorDataCurrent &currentVectors)
{
    return drawPhasesStar(painter, VectorSettingsStatic::IDX_IL1, VectorSettingsStatic::IDX_IL3, currentVectors);
}

bool VectorPaintController::drawPhasesStar(QPainter *painter, int startPhaseIdx, int endPhaseIdx, const VectorDataCurrent &currentVectors)
{
    bool vectorDrawn = false;
    for(int idx=startPhaseIdx; idx<=endPhaseIdx; ++idx) {
        VectorSettingsStatic::VectorType type = VectorSettingsStatic::getVectorType(idx);
        if (currentVectors.m_vectorData[idx].length() > m_vectorSettings.m_lengths.getMinimalValue(type)) {
            QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
                painter, { m_vectorSettings, type }, currentVectors.m_vectorData[idx]);
            VectorPrimitivesPainter::drawVector(painter, { pixLenVector, currentVectors.m_colors[idx] }, m_vectorSettings.m_layout);
            vectorDrawn = true;
        }
    }
    return vectorDrawn;
}

void VectorPaintController::drawVoltageTriangle(QPainter *painter, const VectorDataCurrent &currentVectors)
{
    QVector<VectorPrimitivesPainter::VectorParam> corners(VectorSettingsStatic::COUNT_PHASES);
    for(int idx=VectorSettingsStatic::IDX_UL1; idx<=VectorSettingsStatic::IDX_UL3; ++idx) {
        VectorSettingsStatic::VectorType type = VectorSettingsStatic::getVectorType(idx);
        QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
            painter, { m_vectorSettings, type }, currentVectors.m_vectorData[idx]);
        corners[idx] = { pixLenVector, currentVectors.m_colors[idx] };
    }
    VectorPrimitivesPainter::drawTriangle(painter,
                                          corners[0], corners[1], corners[2],
                                          m_vectorSettings.m_layout);
}

void VectorPaintController::drawLabels(QPainter *painter, const VectorDataCurrent &currentVectors)
{
    for(int idx=0; idx<VectorSettingsStatic::COUNT_VECTORS; ++idx) {
        VectorSettingsStatic::VectorType type = VectorSettingsStatic::getVectorType(idx);
        if (currentVectors.m_vectorData[idx].length() > m_vectorSettings.m_lengths.getMinimalValue(type)) {
            QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
                painter, { m_vectorSettings, type }, currentVectors.m_vectorData[idx]);
            VectorPrimitivesPainter::drawLabel(painter,
                                               { pixLenVector * m_vectorSettings.m_layout.getLabelVectorOvershootFactor(),
                                                currentVectors.m_colors[idx]},
                                               m_vectorSettings.m_layout.getLabelFont(painter),
                                               currentVectors.m_label[idx]);
        }
    }
}

VectorPaintController::VectorDataCurrent VectorPaintController::calc3WireVectorData(const VectorDataCurrent &currentData)
{
    VectorDataCurrent data3Wire(currentData);

    const float sqrt3 = sqrt(3);
    data3Wire.m_vectorData[VectorSettingsStatic::IDX_UL1] = // UL1-UL2
        (currentData.m_vectorData[VectorSettingsStatic::IDX_UL1] - currentData.m_vectorData[VectorSettingsStatic::IDX_UL2]) / sqrt3;
    data3Wire.m_label[VectorSettingsStatic::IDX_UL1] =
        currentData.m_label[VectorSettingsStatic::IDX_UL1] + "-" + currentData.m_label[VectorSettingsStatic::IDX_UL2];

    data3Wire.m_vectorData[VectorSettingsStatic::IDX_UL2] = QVector2D(0,0);

    data3Wire.m_vectorData[VectorSettingsStatic::IDX_UL3] = // UL3-UL2
        (currentData.m_vectorData[VectorSettingsStatic::IDX_UL3] - currentData.m_vectorData[VectorSettingsStatic::IDX_UL2]) / sqrt3;
    data3Wire.m_label[VectorSettingsStatic::IDX_UL3] =
        currentData.m_label[VectorSettingsStatic::IDX_UL3] + "-" + currentData.m_label[VectorSettingsStatic::IDX_UL2];

    data3Wire.m_vectorData[VectorSettingsStatic::IDX_IL2] = QVector2D(0,0);

    return data3Wire;
}
