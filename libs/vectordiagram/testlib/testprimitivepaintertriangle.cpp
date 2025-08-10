#include "testprimitivepaintertriangle.h"
#include "vectorsettingsstatic.h"
#include "vectorprimitivespainter.h"
#include <QVector2D>
#include <complex>

constexpr float vectorLen = 1.0;

TestPrimitivePainterTriangle::TestPrimitivePainterTriangle()
{
    m_settingsGeometry.m_lengths.setNomVoltage(vectorLen);
    m_settingsGeometry.m_lengths.setNomCurrent(vectorLen);
}

void TestPrimitivePainterTriangle::paint(QPainter *painter)
{
    VectorSettingsStatic::setFontForLabels(painter); // for reproducability

    QColor circleCoordColor("grey");
    VectorPrimitivesPainter::drawCoordCross(painter, circleCoordColor);
    VectorPrimitivesPainter::drawCircle(painter, m_settingsGeometry.m_lengths, circleCoordColor);

    drawTriangle(painter);
}

void TestPrimitivePainterTriangle::drawTriangle(QPainter *painter)
{
    constexpr int dark = 130;
    QVector<QColor> colors{QColor("red").darker(dark), QColor("yellow").darker(dark), QColor("blue").darker(dark)};
    QVector<VectorPrimitivesPainter::VectorData> corners(colors.size());
    for(int idx=0; idx<colors.count(); ++idx) {
        std::complex<double> corner = std::polar<double>(vectorLen, idx*120 * (2*M_PI/360));
        corners[idx] = { QVector2D(corner.real(),corner.imag()), colors[idx] };
    }

    const float nomValue = m_settingsGeometry.m_lengths.getNominalUOrI(0);
    VectorPrimitivesPainter::drawTriangle(painter, m_settingsGeometry, nomValue,
                                          corners[0], corners[1], corners[2]);
}
