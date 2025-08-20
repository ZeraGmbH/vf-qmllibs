#include "vectorlabelcollisionavoider.h"
#include "vectorconstants.h"
#include "vectorpaintcalc.h"
#include <math.h>

PixVectorsShown VectorLabelCollisionAvoider::getCollisionAdjVectors(const PixVectorsShown &shownVectors,
                                                                    const VectorSettingsUser::VectorType &vectorType)
{
    PixVectorsShown adjVectors = shownVectors;
    QVector<bool> iPhaseWasSwapped(VectorConstants::COUNT_VECTORS);
    for (int idxU=VectorConstants::IDX_UL1; idxU<=VectorConstants::IDX_UL3; idxU++) {
        const PixVectorShown &inVectorU = shownVectors[idxU];
        if (!inVectorU.shown)
            continue;
        const float angleU = VectorPaintCalc::normalizeAngle(
            atan2(inVectorU.wantedPixVectorLabel.y(), inVectorU.wantedPixVectorLabel.x()));
        float offsetAngleU;
        float offsetAngleI;
         // direction as set by vector standard (attow all clockwise)
        if (vectorType != VectorSettingsUser::VectorType::THREE_PHASE) {
            offsetAngleU = degToRad(-6);
            offsetAngleI = -offsetAngleU;
        }
        else {
            offsetAngleU = degToRad(-10); // UL1-UL2 / UL3-UL2 need more rotation
            offsetAngleI = degToRad(6);
        }
        for(int idxI=VectorConstants::IDX_IL1; idxI<=VectorConstants::IDX_IL3; idxI++) {
            if (iPhaseWasSwapped[idxI])
                continue;
            const PixVectorShown &inVectorI = shownVectors[idxI];
            if (!inVectorI.shown)
                continue;

            const float angleI = VectorPaintCalc::normalizeAngle(
                atan2(inVectorI.wantedPixVectorLabel.y(), inVectorI.wantedPixVectorLabel.x()));
            float diffAngle = VectorPaintCalc::normalizeAngle(angleU - angleI);
            // Note: To avoid failing tests on different build environments, do not use
            // integer values here. Tests use intergers and collision decisions can vary.
            constexpr float minDiff = degToRad(0.25); // avoid cos(φ) = 0 toggle
            constexpr float maxDiff = degToRad(28.5);   // long labels in 3Wire
            if(diffAngle > minDiff && diffAngle < maxDiff) {
                offsetAngleU = -offsetAngleU;
                offsetAngleI = -offsetAngleI;
                iPhaseWasSwapped[idxI] = true;
            }
            const QVector2D turnedVectorU = VectorPaintCalc::rotateVector(inVectorU.wantedPixVectorLabel, offsetAngleU);
            const QVector2D turnedVectorI = VectorPaintCalc::rotateVector(inVectorI.wantedPixVectorLabel, offsetAngleI);
            adjVectors[idxU].wantedPixVectorLabel = turnedVectorU;
            adjVectors[idxI].wantedPixVectorLabel = turnedVectorI;
        }
    }
    return adjVectors;
}
