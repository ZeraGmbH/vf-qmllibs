#include "testprimitivepainterstar.h"
#include "vectorpaintcalc.h"
#include "vectorconstants.h"
#include "vectorprimitivespainter.h"
#include <QVector2D>
#include <complex>

constexpr float vectorLen = 1.0;

TestPrimitivePainterStar::TestPrimitivePainterStar()
{
    m_vectorSettings.m_lengths.setNomVoltage(vectorLen);
    m_vectorSettings.m_lengths.setNomCurrent(vectorLen);
    m_vectorSettings.m_lengths.setNominalSelection(VectorNominals::NOMINAL);
}

void TestPrimitivePainterStar::paint(QPainter *painter)
{
    painter->setFont(m_vectorSettings.m_layout.getLabelFont(painter)); // for reproducability

    VectorPrimitivesPainter::drawCoordCross(painter, m_vectorSettings.m_layout);
    VectorPrimitivesPainter::drawCircle(painter, m_vectorSettings.m_lengths, m_vectorSettings.m_layout);

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
        PhaseType phaseType = VectorConstants::getVectorType(idx);
        if (vectors[idx].length() > m_vectorSettings.m_lengths.getMinimalValue(phaseType)) {
            QVector2D pixLenVector = VectorPaintCalc::calcPixVec(
                painter, { m_vectorSettings, phaseType }, vectors[idx]);
            VectorPrimitivesPainter::drawVector(painter,
                                                { phaseType, pixLenVector, colors[idx] },
                                                m_vectorSettings.m_layout);
            VectorPrimitivesPainter::drawLabel(painter,
                                               {phaseType,
                                                pixLenVector * m_vectorSettings.m_layout.getLabelVectorOvershootFactor(),
                                                colors[idx]},
                                               m_vectorSettings.m_layout.getLabelFont(painter),
                                               labels[idx]);
        }
    }
}
