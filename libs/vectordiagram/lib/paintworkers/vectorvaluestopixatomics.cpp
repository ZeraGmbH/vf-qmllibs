#include "vectorvaluestopixatomics.h"
#include "vectorpaintcalc.h"
#include "vectorpixatomicspainter.h"
#include "vectorlabelcollisionavoider.h"
#include <math.h>

bool VectorValuesToPixAtomics::drawVoltageStar(QPainter *painter, const VectorSettings &vectorSettings, const VectorDataCurrent &currentVectors)
{
    return drawPhasesStar(painter, VectorConstants::IDX_U_START, VectorConstants::IDX_U_END,
                          vectorSettings, currentVectors);
}

bool VectorValuesToPixAtomics::drawCurrentStar(QPainter *painter, const VectorSettings &vectorSettings, const VectorDataCurrent &currentVectors)
{
    return drawPhasesStar(painter, VectorConstants::IDX_I_START, VectorConstants::IDX_I_END,
                          vectorSettings, currentVectors);
}

bool VectorValuesToPixAtomics::drawPhasesStar(QPainter *painter, int startPhaseIdx, int endPhaseIdx, const VectorSettings &vectorSettings, const VectorDataCurrent &currentVectors)
{
    bool vectorDrawn = false;
    for(int idx=startPhaseIdx; idx<=endPhaseIdx; ++idx) {
        PhaseType phaseType = VectorConstants::getVectorType(idx);
        if (currentVectors.m_vectorData[idx].length() > vectorSettings.m_lengths.getMinimalValue(phaseType)) {
            QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
                painter, { vectorSettings, phaseType }, currentVectors.m_vectorData[idx]);
            VectorPixAtomicsPainter::drawVector(painter,
                                                { phaseType, pixLenVector, currentVectors.m_colors[idx] },
                                                vectorSettings.m_layout);
            vectorDrawn = true;
        }
    }
    return vectorDrawn;
}

void VectorValuesToPixAtomics::drawVoltageTriangle(QPainter *painter, const VectorSettings &vectorSettings, const VectorDataCurrent &currentVectors)
{
    QVector<VectorPixAtomicsPainter::VectorParam> corners(VectorConstants::COUNT_PHASES);
    for(int idx=VectorConstants::IDX_U_START; idx<=VectorConstants::IDX_U_END; ++idx) {
        PhaseType phaseType = VectorConstants::getVectorType(idx);
        QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
            painter, { vectorSettings, phaseType }, currentVectors.m_vectorData[idx]);
        corners[idx] = { phaseType, pixLenVector, currentVectors.m_colors[idx] };
    }
    VectorPixAtomicsPainter::drawTriangle(painter,
                                          corners[0], corners[1], corners[2],
                                          vectorSettings.m_layout);
}

void VectorValuesToPixAtomics::drawLabels(QPainter *painter, const VectorSettings &vectorSettings,
                                          const VectorDataCurrent &currentVectors)
{
    const PixVectorsShown shownVectors = getShownLabelsAndPixLenWanted(painter, vectorSettings, currentVectors);

    PixVectorsShown collisionAdjVectors = shownVectors;
    if (vectorSettings.m_layout.getLabelCollisionAvoidance()) {
        collisionAdjVectors = VectorLabelCollisionAvoider::getCollisionAdjVectors(shownVectors,
                                                                                  vectorSettings.m_user.getVectorType());
    }

    for (int idx=0; idx<collisionAdjVectors.size(); idx++) {
        const PixVectorShown &labelVector = collisionAdjVectors[idx];
        if (!labelVector.shown)
            continue;
        const QString &label = currentVectors.m_label[idx];
        const QVector2D pixLenVectorLabelAdj = limitLabelVectorLen(painter, labelVector.wantedPixVectorLabel, label);
        PhaseType phaseType = VectorConstants::getVectorType(idx);
        VectorPixAtomicsPainter::drawLabel(painter,
                                           { phaseType, pixLenVectorLabelAdj, currentVectors.m_colors[idx] },
                                           vectorSettings.m_layout.getLabelFont(painter),
                                           label);
    }
}

PixVectorsShown VectorValuesToPixAtomics::getShownLabelsAndPixLenWanted(
    const QPainter *painter, const VectorSettings &vectorSettings, const VectorDataCurrent &currentVectors)
{
    PixVectorsShown shownLabels(currentVectors.m_vectorData.size());
    for (int idx=0; idx<VectorConstants::COUNT_VECTORS; ++idx) {
        PhaseType phaseType = VectorConstants::getVectorType(idx);
        if (currentVectors.m_vectorData[idx].length() > vectorSettings.m_lengths.getMinimalValue(phaseType)) {
            const QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
                painter, { vectorSettings, phaseType }, currentVectors.m_vectorData[idx]);
            const QVector2D pixLenVectorLabel = pixLenVector * vectorSettings.m_layout.getLabelVectorOvershootFactor();
            shownLabels[idx] = {pixLenVectorLabel, true};
        }
        else
            shownLabels[idx] = {QVector2D(), false};
    }
    return shownLabels;
}

QVector2D VectorValuesToPixAtomics::limitLabelVectorLen(const QPainter *painter, const QVector2D &pixLenVector,
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

QVector2D VectorValuesToPixAtomics::lengthenLabelTooShortVector(const QPainter *painter, const QVector2D &pixLenVector)
{
    const float lenAvail = VectorPaintCalc::getClipSquareLen(painter) / 2;
    constexpr float minLabelLenRel = 0.4;
    const float minLabelLen = lenAvail * minLabelLenRel;
    if (pixLenVector.length() > minLabelLen)
        return pixLenVector;
    return VectorPaintCalc::calcVectorOtherLen(pixLenVector, minLabelLen);
}
