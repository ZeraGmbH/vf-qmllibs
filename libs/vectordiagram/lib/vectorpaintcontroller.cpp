#include "vectorpaintcontroller.h"
#include "vectorpaintcalc.h"
#include "vectorprimitivespainter.h"

VectorPaintController::VectorPaintController() :
    m_vectorSettings(std::make_shared<VectorSettings>())
{
}

std::shared_ptr<VectorSettings> VectorPaintController::getVectorSettings() const
{
    return m_vectorSettings;
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
    painter->setFont(m_vectorSettings->m_layout.getLabelFont(painter)); // yeah for the sake reproducability of test SVGs

    if(m_vectorSettings->m_layout.getCoordCrossVisible())
        VectorPrimitivesPainter::drawCoordCross(painter, m_vectorSettings->m_layout);
    if(m_vectorSettings->m_layout.getCircleVisible())
        VectorPrimitivesPainter::drawCircle(painter, m_vectorSettings->m_lengths, m_vectorSettings->m_layout);

    const VectorSettingsUser::VectorType vectorType = m_vectorSettings->m_user.getVectorType();
    VectorDataCurrent currentData = {m_inVectorColors, m_inVectorLabels, m_inVectors};
    if (vectorType == VectorSettingsUser::VectorType::THREE_PHASE)
        currentData = calc3WireVectorData(currentData);

    updateSettingsMaxValues(m_vectorSettings->m_lengths, currentData);
    setAngleSettingsFromStandard(m_vectorSettings, currentData);

    bool vectorDrawn = false;
    switch (vectorType) {
    case VectorSettingsUser::VectorType::STAR:
    case VectorSettingsUser::VectorType::THREE_PHASE:
        if (VectorGroupsPainter::drawCurrentStar(painter, *m_vectorSettings, currentData))
            vectorDrawn = true;
        if (VectorGroupsPainter::drawVoltageStar(painter, *m_vectorSettings, currentData))
            vectorDrawn = true;
        break;
    case VectorSettingsUser::VectorType::TRIANGLE:
        if (VectorGroupsPainter::drawCurrentStar(painter, *m_vectorSettings, currentData))
            vectorDrawn = true;
        VectorGroupsPainter::drawVoltageTriangle(painter, *m_vectorSettings, currentData);
        break;
    }
    VectorGroupsPainter::drawLabels(painter, *m_vectorSettings, currentData);
    if(vectorDrawn)
        VectorPrimitivesPainter::drawCoordCenterDot(painter, m_vectorSettings->m_layout);
}

VectorDataCurrent VectorPaintController::calc3WireVectorData(const VectorDataCurrent &currentData)
{
    VectorDataCurrent data3Wire(currentData);

    const float sqrt3 = sqrt(3);
    data3Wire.m_vectorData[VectorConstants::IDX_UL1] = // UL1-UL2
        (currentData.m_vectorData[VectorConstants::IDX_UL1] - currentData.m_vectorData[VectorConstants::IDX_UL2]) / sqrt3;
    data3Wire.m_label[VectorConstants::IDX_UL1] =
        currentData.m_label[VectorConstants::IDX_UL1] + "-" + currentData.m_label[VectorConstants::IDX_UL2];

    data3Wire.m_vectorData[VectorConstants::IDX_UL2] = QVector2D(0,0);

    data3Wire.m_vectorData[VectorConstants::IDX_UL3] = // UL3-UL2
        (currentData.m_vectorData[VectorConstants::IDX_UL3] - currentData.m_vectorData[VectorConstants::IDX_UL2]) / sqrt3;
    data3Wire.m_label[VectorConstants::IDX_UL3] =
        currentData.m_label[VectorConstants::IDX_UL3] + "-" + currentData.m_label[VectorConstants::IDX_UL2];

    data3Wire.m_vectorData[VectorConstants::IDX_IL2] = QVector2D(0,0);

    return data3Wire;
}

void VectorPaintController::setAngleSettingsFromStandard(std::shared_ptr<VectorSettings> vectorSettings,
                                                         const VectorDataCurrent& currentVectors)
{
    switch(vectorSettings->m_user.getVectorStandard()) {
    case VectorSettingsUser::VectorStandard::DIN: {
        const float angleUL1 = atan2(currentVectors.m_vectorData[VectorConstants::IDX_UL1].y(),
                                     currentVectors.m_vectorData[VectorConstants::IDX_UL1].x());
        vectorSettings->m_angles.setRotationDirection(RotationDirection::Clockwise);
        vectorSettings->m_angles.setOffsetAngle(-degToRad(90)-angleUL1);
        break;
    }
    case VectorSettingsUser::VectorStandard::IEC: {
        const float angleIL1 = atan2(currentVectors.m_vectorData[VectorConstants::IDX_IL1].y(),
                                     currentVectors.m_vectorData[VectorConstants::IDX_IL1].x());
        // Interesting: We expected VectorSettingsAngles::Mathematical but that is true
        // only if angle passed in are in IEC sytyle too. ATTOW We come in as DIN always
        vectorSettings->m_angles.setRotationDirection(RotationDirection::Clockwise);
        vectorSettings->m_angles.setOffsetAngle(-angleIL1);
        break;
    }
    case VectorSettingsUser::VectorStandard::ANSI: {
        const float angleUL1 = atan2(currentVectors.m_vectorData[VectorConstants::IDX_UL1].y(),
                                     currentVectors.m_vectorData[VectorConstants::IDX_UL1].x());
        vectorSettings->m_angles.setRotationDirection(RotationDirection::Clockwise);
        vectorSettings->m_angles.setOffsetAngle(-angleUL1);
        break;
    }
    }
}

void VectorPaintController::updateSettingsMaxValues(VectorSettingsLengths &lengthSettings,
                                                    const VectorDataCurrent &currentVectors)
{
    float maxU = 1e-12;
    const float minU = lengthSettings.getMinimalValue(PhaseType::TYPE_U);
    for (int idx=VectorConstants::IDX_UL1; idx<=VectorConstants::IDX_UL3; ++idx) {
        const float currU = currentVectors.m_vectorData[idx].length();
        if (currU > minU && currU > maxU)
            maxU = currU;
    }
    lengthSettings.setMaxU(maxU);

    float maxI = 1e-12;
    const float minI = lengthSettings.getMinimalValue(PhaseType::TYPE_I);
    for (int idx=VectorConstants::IDX_IL1; idx<=VectorConstants::IDX_IL3; ++idx) {
        const float currI = currentVectors.m_vectorData[idx].length();
        if (currI > minI && currI > maxI)
            maxI = currI;
    }
    lengthSettings.setMaxI(maxI);
}
