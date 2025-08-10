#include "testprimitivepainterstar.h"
#include "vectorsettingsstatic.h"
#include "vectorprimitivespainter.h"
#include <QVector2D>
#include <complex>

constexpr float vectorLen = 1.0;

TestPrimitivePainterStar::TestPrimitivePainterStar()
{
    m_settingsGeometry.m_lengths.setNomVoltage(vectorLen);
    m_settingsGeometry.m_lengths.setNomCurrent(vectorLen);
}

void TestPrimitivePainterStar::paint(QPainter *painter)
{
    VectorSettingsStatic::setFontForLabels(painter); // for reproducability

    QColor circleCoordColor("grey");
    VectorPrimitivesPainter::drawCoordCross(painter, circleCoordColor);
    VectorPrimitivesPainter::drawCircle(painter, m_settingsGeometry.m_lengths, circleCoordColor);

    draw2Vectors(painter);
}

void TestPrimitivePainterStar::draw2Vectors(QPainter *painter)
{
    constexpr int dark = 130;
    QVector<QColor> colors{QColor("red").darker(dark), QColor("red").lighter()};

    constexpr float angle30 = 30 * (2*M_PI/360);
    std::complex<double> uRawValue[] = { std::polar<double>(vectorLen, 0), std::polar<double>(vectorLen*0.5, angle30)};
    QVector<QVector2D> vectors(colors.size());
    for(int idx=0; idx<colors.count(); ++idx) {
        vectors[idx].setX(uRawValue[idx].real());
        vectors[idx].setY(uRawValue[idx].imag());
    }

    for(int idx=0; idx<colors.count(); ++idx) {
        if (vectors[idx].length() > m_settingsGeometry.m_lengths.getMinimalUOrI(idx)) {
            const float nomValue = m_settingsGeometry.m_lengths.getNominalUOrI(idx);
            VectorPrimitivesPainter::drawVector(painter, m_settingsGeometry,
                                                nomValue, {vectors[idx], colors[idx]});
        }
    }
}
