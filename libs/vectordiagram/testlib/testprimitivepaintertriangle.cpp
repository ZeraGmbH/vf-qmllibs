#include "testprimitivepaintertriangle.h"
#include "vectorpaintcalc.h"
#include "vectorconstants.h"
#include "vectorpixatomicspainter.h"
#include <QVector2D>
#include <complex>

constexpr float vectorLen = 1.0;

TestPrimitivePainterTriangle::TestPrimitivePainterTriangle()
{
    m_vectorSettings.m_lengths.setNomVoltage(vectorLen);
    m_vectorSettings.m_lengths.setNomCurrent(vectorLen);
    m_vectorSettings.m_lengths.setNominalSelection(VectorSettingsLengths::VectorNominals::NOMINAL);
}

void TestPrimitivePainterTriangle::paint(QPainter *painter)
{
    painter->setFont(m_vectorSettings.m_layout.getLabelFont(painter)); // for reproducability

    VectorPixAtomicsPainter::drawCoordCross(painter, m_vectorSettings.m_layout);
    VectorPixAtomicsPainter::drawCircle(painter, m_vectorSettings.m_lengths, m_vectorSettings.m_layout);

    drawTriangle(painter);
}

void TestPrimitivePainterTriangle::drawTriangle(QPainter *painter)
{
    constexpr int dark = 130;
    QVector<QColor> colors{QColor("red").darker(dark), QColor("yellow"), QColor("blue").darker(dark)};
    Q_ASSERT(VectorConstants::COUNT_PHASES == colors.size());

    QVector<VectorPixAtomicsPainter::VectorParam> corners(VectorConstants::COUNT_PHASES);
    QVector<QVector2D> vectorPixLens(VectorConstants::COUNT_PHASES);
    for(int idx=0; idx<colors.count(); ++idx) {
        std::complex<double> corner = std::polar<double>(vectorLen, degToRad(idx*120));
        QVector2D value = QVector2D(corner.real(),corner.imag());
        vectorPixLens[idx] = VectorPaintCalc::calcPixVec(painter, { m_vectorSettings, PhaseType::TYPE_U}, value);
        corners[idx] = { PhaseType::TYPE_U, vectorPixLens[idx], colors[idx] };
    }
    VectorPixAtomicsPainter::drawTriangle(painter,
                                          corners[0], corners[1], corners[2],
                                          m_vectorSettings.m_layout);
}
