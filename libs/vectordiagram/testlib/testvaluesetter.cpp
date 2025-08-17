#include "testvaluesetter.h"
#include "vectorpaintcalc.h"
#include <complex>

void TestValueSetter::setSymmetricValues(VectorPaintController *painter, double uValue, double iValue, double iAngle)
{
    int dark = 130;
    QVector<QColor> colors{QColor("red").darker(dark), QColor("yellow"), QColor("blue").darker(dark),
                           QColor("red").lighter(), QColor("yellow").lighter(160), QColor("blue").lighter()};

    for (int i=0; i<VectorConstants::COUNT_PHASES; i++) {
        int uIdx = i;
        int iIdx = i + VectorConstants::COUNT_PHASES;
        painter->setVectorColor(uIdx, colors[uIdx]);
        painter->setVectorColor(iIdx, colors[iIdx]);

        painter->setVectorLabel(i, QString("UL%1").arg(i+1));
        painter->setVectorLabel(i+VectorConstants::COUNT_PHASES, QString("IL%1").arg(i+1));

        const double uPhi = degToRad(i*120);
        std::complex<double> uRawValue = std::polar<double>(uValue, uPhi);
        painter->setVector(i, QVector2D(uRawValue.real(), uRawValue.imag()));

        const double iPhi = uPhi + degToRad(iAngle);
        std::complex<double> iRawValue = std::polar<double>(iValue, iPhi);
        painter->setVector(i+VectorConstants::COUNT_PHASES, QVector2D(iRawValue.real(), iRawValue.imag()));
    }
}

void TestValueSetter::setNominalUI(VectorPaintController &vectorPainter, float nominal)
{
    VectorSettingsLengths &lengthSettings = vectorPainter.getVectorSettings()->m_lengths;
    lengthSettings.setNominalSelection(VectorSettingsLengths::VectorNominals::NOMINAL);
    lengthSettings.setNomCurrent(nominal);
    lengthSettings.setNomVoltage(nominal);
}
