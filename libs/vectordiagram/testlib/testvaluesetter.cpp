#include "testvaluesetter.h"
#include "vectorpaintcalc.h"
#include <complex>

const QVector<QString> TestValueSetter::m_testLabels{
    "UL1", "UL2", "IL3",
    "IL1", "IL2", "IL3"
};

static constexpr int dark = 130;
const QVector<QColor> TestValueSetter::m_testColors{
    QColor("red").darker(dark), QColor("yellow"), QColor("blue").darker(dark),
    QColor("red").lighter(), QColor("yellow").lighter(160), QColor("blue").lighter()
};

void TestValueSetter::setSymmetricValues(VectorPaintController *painter, double uValue, double iValue, double iAngle)
{
    for (int i=0; i<VectorConstants::COUNT_PHASES; i++) {
        const int uPhase = i;
        const int iPhase = i+VectorConstants::COUNT_PHASES;

        painter->setVectorColor(uPhase, m_testColors[uPhase]);
        painter->setVectorColor(iPhase, m_testColors[iPhase]);

        painter->setVectorLabel(uPhase, m_testLabels[uPhase]);
        painter->setVectorLabel(iPhase, m_testLabels[iPhase]);

        const double uPhi = degToRad(i*120);
        std::complex<double> uRawValue = std::polar<double>(uValue, uPhi);
        painter->setVector(uPhase, QVector2D(uRawValue.real(), uRawValue.imag()));

        const double iPhi = uPhi + degToRad(iAngle);
        std::complex<double> iRawValue = std::polar<double>(iValue, iPhi);
        painter->setVector(iPhase, QVector2D(iRawValue.real(), iRawValue.imag()));
    }
}

void TestValueSetter::setNominalUI(VectorPaintController &vectorPainter, float nominal)
{
    VectorSettingsLengths &lengthSettings = vectorPainter.getVectorSettings()->m_lengths;
    lengthSettings.setNominalSelection(VectorSettingsLengths::VectorNominals::NOMINAL);
    lengthSettings.setNomCurrent(nominal);
    lengthSettings.setNomVoltage(nominal);
}
