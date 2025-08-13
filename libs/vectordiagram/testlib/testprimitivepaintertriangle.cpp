#include "testprimitivepaintertriangle.h"
#include "vectorpaintcalc.h"
#include "vectorsettingsstatic.h"
#include "vectorprimitivespainter.h"
#include <QVector2D>
#include <complex>

constexpr float vectorLen = 1.0;

TestPrimitivePainterTriangle::TestPrimitivePainterTriangle()
{
    m_vectorSettings.m_lengths.setNomVoltage(vectorLen);
    m_vectorSettings.m_lengths.setNomCurrent(vectorLen);
    m_vectorSettings.m_lengths.setNominalSelection(VectorNominals::NOMINAL);
}

void TestPrimitivePainterTriangle::paint(QPainter *painter)
{
    painter->setFont(m_vectorSettings.m_layout.getLabelFont(painter)); // for reproducability

    VectorPrimitivesPainter::drawCoordCross(painter, m_vectorSettings.m_layout);
    VectorPrimitivesPainter::drawCircle(painter, m_vectorSettings.m_lengths, m_vectorSettings.m_layout);

    drawTriangle(painter);
}

void TestPrimitivePainterTriangle::drawTriangle(QPainter *painter)
{
    constexpr int dark = 130;
    QVector<QColor> colors{QColor("red").darker(dark), QColor("yellow"), QColor("blue").darker(dark)};
    Q_ASSERT(VectorSettingsStatic::COUNT_PHASES == colors.size());

    QVector<VectorPrimitivesPainter::VectorParam> corners(VectorSettingsStatic::COUNT_PHASES);
    QVector<QVector2D> vectorPixLens(VectorSettingsStatic::COUNT_PHASES);
    for(int idx=0; idx<colors.count(); ++idx) {
        std::complex<double> corner = std::polar<double>(vectorLen, degToRad(idx*120));
        QVector2D value = QVector2D(corner.real(),corner.imag());
        vectorPixLens[idx] = VectorPaintCalc::calcPixVec(painter, { m_vectorSettings, VectorSettingsStatic::TYPE_U}, value);
        corners[idx] = { vectorPixLens[idx], colors[idx] };
    }
    VectorPrimitivesPainter::drawTriangle(painter,
                                          corners[0], corners[1], corners[2],
                                          m_vectorSettings.m_layout);
}
