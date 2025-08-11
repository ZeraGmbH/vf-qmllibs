#include "testprimitivepainterstar.h"
#include "vectorpaintcalc.h"
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

    constexpr float angle30 = degToRad(30);
    std::complex<double> uRawValue[] = { std::polar<double>(vectorLen, 0), std::polar<double>(vectorLen*0.5, angle30)};
    QVector<QVector2D> vectors(colors.size());
    for(int idx=0; idx<colors.count(); ++idx) {
        vectors[idx].setX(uRawValue[idx].real());
        vectors[idx].setY(uRawValue[idx].imag());
    }

    for(int idx=0; idx<colors.count(); ++idx) {
        VectorSettingsStatic::VectorType type = VectorSettingsStatic::getVectorType(idx);
        if (vectors[idx].length() > m_settingsGeometry.m_lengths.getMinimalValue(type)) {
            const float lineWidth = VectorSettingsStatic::getVectorLineWidth(painter);
            QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
                painter, { m_settingsGeometry, type }, vectors[idx]);
            VectorPrimitivesPainter::drawVector(painter, { pixLenVector, colors[idx] }, lineWidth);
        }
    }
}
