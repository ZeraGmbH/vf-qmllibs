#include "vectorgroupspainter.h"
#include "vectorpaintcalc.h"
#include "vectorprimitivespainter.h"
#include <math.h>

bool VectorGroupsPainter::drawVoltageStar(QPainter *painter, const VectorSettings &vectorSettings, const VectorDataCurrent &currentVectors)
{
    return drawPhasesStar(painter, VectorConstants::IDX_UL1, VectorConstants::IDX_UL3,
                          vectorSettings, currentVectors);
}

bool VectorGroupsPainter::drawCurrentStar(QPainter *painter, const VectorSettings &vectorSettings, const VectorDataCurrent &currentVectors)
{
    return drawPhasesStar(painter, VectorConstants::IDX_IL1, VectorConstants::IDX_IL3,
                          vectorSettings, currentVectors);
}

bool VectorGroupsPainter::drawPhasesStar(QPainter *painter, int startPhaseIdx, int endPhaseIdx, const VectorSettings &vectorSettings, const VectorDataCurrent &currentVectors)
{
    bool vectorDrawn = false;
    for(int idx=startPhaseIdx; idx<=endPhaseIdx; ++idx) {
        PhaseType phaseType = VectorConstants::getVectorType(idx);
        if (currentVectors.m_vectorData[idx].length() > vectorSettings.m_lengths.getMinimalValue(phaseType)) {
            QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
                painter, { vectorSettings, phaseType }, currentVectors.m_vectorData[idx]);
            VectorPrimitivesPainter::drawVector(painter,
                                                { phaseType, pixLenVector, currentVectors.m_colors[idx] },
                                                vectorSettings.m_layout);
            vectorDrawn = true;
        }
    }
    return vectorDrawn;
}

void VectorGroupsPainter::drawVoltageTriangle(QPainter *painter, const VectorSettings &vectorSettings, const VectorDataCurrent &currentVectors)
{
    QVector<VectorPrimitivesPainter::VectorParam> corners(VectorConstants::COUNT_PHASES);
    for(int idx=VectorConstants::IDX_UL1; idx<=VectorConstants::IDX_UL3; ++idx) {
        PhaseType phaseType = VectorConstants::getVectorType(idx);
        QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
            painter, { vectorSettings, phaseType }, currentVectors.m_vectorData[idx]);
        corners[idx] = { phaseType, pixLenVector, currentVectors.m_colors[idx] };
    }
    VectorPrimitivesPainter::drawTriangle(painter,
                                          corners[0], corners[1], corners[2],
                                          vectorSettings.m_layout);
}

void VectorGroupsPainter::drawLabels(QPainter *painter, const VectorSettings &vectorSettings,
                                     const VectorDataCurrent &currentVectors)
{
    const ShownLabels shownLabels = getShownLabelsAndPixLenWanted(painter, vectorSettings, currentVectors);

    // TODO angles/collision

    for (const ShownLabel &shownLabel : shownLabels) {
        int idx = shownLabel.idx;
        const QString &label = currentVectors.m_label[idx];
        const QVector2D pixLenVectorLabelAdj = limitLabelVectorLen(painter, shownLabel.wantedPixLenLabel, label);
        PhaseType phaseType = VectorConstants::getVectorType(idx);
        VectorPrimitivesPainter::drawLabel(painter,
                                           { phaseType, pixLenVectorLabelAdj, currentVectors.m_colors[idx] },
                                           vectorSettings.m_layout.getLabelFont(painter),
                                           label);
    }
}

VectorDataCurrent VectorGroupsPainter::calc3WireVectorData(const VectorDataCurrent &currentData)
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

VectorGroupsPainter::ShownLabels VectorGroupsPainter::getShownLabelsAndPixLenWanted(
    const QPainter *painter, const VectorSettings &vectorSettings, const VectorDataCurrent &currentVectors)
{
    ShownLabels shownLabels;
    for (int idx=0; idx<VectorConstants::COUNT_VECTORS; ++idx) {
        PhaseType phaseType = VectorConstants::getVectorType(idx);
        if (currentVectors.m_vectorData[idx].length() > vectorSettings.m_lengths.getMinimalValue(phaseType)) {
            const QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
                painter, { vectorSettings, phaseType }, currentVectors.m_vectorData[idx]);
            const QVector2D pixLenVectorLabel = pixLenVector * vectorSettings.m_layout.getLabelVectorOvershootFactor();
            shownLabels.append({pixLenVectorLabel, idx});
        }
    }
    return shownLabels;
}

QVector2D VectorGroupsPainter::limitLabelVectorLen(const QPainter *painter, const QVector2D &pixLenVector,
                                                   const QString &label)
{
    const QPointF textPixSize = VectorPaintCalc::approxFontMetrics(painter, label);
    const float horizTextEnd = fabs(pixLenVector.x()) + textPixSize.x() / 2;
    const float vertTextEnd = fabs(pixLenVector.y()) + textPixSize.y() / 2;
    const float maxTextEnd = std::max(horizTextEnd, vertTextEnd);
    const float lenAvail = VectorPaintCalc::getClipSquareLen(painter) / 2;
    const float overshootRatio = maxTextEnd / lenAvail;
    constexpr float maxOvershootRatio = 0.975; // deduced by tests
    if (overshootRatio < maxOvershootRatio) // within square
        return lengthenLabelTooShortVector(painter, pixLenVector);
    return pixLenVector * maxOvershootRatio / overshootRatio;
}

QVector2D VectorGroupsPainter::lengthenLabelTooShortVector(const QPainter *painter, const QVector2D &pixLenVector)
{
    const float lenAvail = VectorPaintCalc::getClipSquareLen(painter) / 2;
    constexpr float minLabelLenRel = 0.4;
    const float minLabelLen = lenAvail * minLabelLenRel;
    if (pixLenVector.length() > minLabelLen)
        return pixLenVector;
    return VectorPaintCalc::calcVectorOtherLen(pixLenVector, minLabelLen);
}
