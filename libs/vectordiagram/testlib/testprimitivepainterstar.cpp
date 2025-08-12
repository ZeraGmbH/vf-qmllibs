#include "testprimitivepainterstar.h"
#include "vectorpaintcalc.h"
#include "vectorsettingsstatic.h"
#include "vectorprimitivespainter.h"
#include <QVector2D>
#include <complex>

constexpr float vectorLen = 1.0;

TestPrimitivePainterStar::TestPrimitivePainterStar()
{
    m_vectorSettings.m_lengths.setNomVoltage(vectorLen);
    m_vectorSettings.m_lengths.setNomCurrent(vectorLen);
}

void TestPrimitivePainterStar::paint(QPainter *painter)
{
    painter->setFont(m_vectorSettings.m_layout.getDefaultFont(painter)); // for reproducability

    QColor circleCoordColor("grey");
    const float coordCircleLineWidth = VectorSettingsStatic::getCoordCrossAndCircleLineWidth(painter);
    VectorPrimitivesPainter::drawCoordCross(painter, circleCoordColor, coordCircleLineWidth);
    VectorPrimitivesPainter::drawCircle(painter, m_vectorSettings.m_lengths, circleCoordColor, coordCircleLineWidth);

    draw2Vectors(painter);
}

void TestPrimitivePainterStar::draw2Vectors(QPainter *painter)
{
    constexpr int dark = 130;
    QVector<QColor> colors{QColor("red").darker(dark), QColor("red").lighter()};
    QStringList labels = QStringList() << "UL1-UL2" << "IL1";

    constexpr float angle30 = degToRad(30);
    std::complex<double> uRawValue[] = { std::polar<double>(vectorLen, 0), std::polar<double>(vectorLen*0.5, angle30)};
    QVector<QVector2D> vectors(colors.size());
    for(int idx=0; idx<colors.count(); ++idx) {
        vectors[idx].setX(uRawValue[idx].real());
        vectors[idx].setY(uRawValue[idx].imag());
    }

    for(int idx=0; idx<colors.count(); ++idx) {
        VectorSettingsStatic::VectorType type = VectorSettingsStatic::getVectorType(idx);
        if (vectors[idx].length() > m_vectorSettings.m_lengths.getMinimalValue(type)) {
            const float lineWidth = VectorSettingsStatic::getVectorLineWidth(painter);
            QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
                painter, { m_vectorSettings, type }, vectors[idx]);
            VectorPrimitivesPainter::drawVector(painter, { pixLenVector, colors[idx] }, lineWidth);
            VectorPrimitivesPainter::drawLabel(painter,
                                               { pixLenVector * m_vectorSettings.m_layout.getLabelVectorOvershootFactor(), colors[idx]},
                                               m_vectorSettings.m_layout.getDefaultFont(painter),
                                               labels[idx]);
        }
    }
}
