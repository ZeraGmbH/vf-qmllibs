#include "testprimitivepainterlabel.h"
#include "vectorpaintcalc.h"
#include "vectorpixatomicspainter.h"
#include <QVector2D>
#include <complex>

constexpr float vectorLen = 1.0;

TestPrimitivePainterLabel::TestPrimitivePainterLabel()
{
    m_vectorSettings.m_lengths.setNomVoltage(vectorLen);
    m_vectorSettings.m_lengths.setNomCurrent(vectorLen);
    m_vectorSettings.m_lengths.setNominalSelection(VectorSettingsLengths::VectorNominals::NOMINAL);
    m_vectorSettings.m_angles.setRotationDirection(RotationDirection::Clockwise);
    m_vectorSettings.m_angles.setOffsetAngle(degToRad(-90));
}

void TestPrimitivePainterLabel::paint(QPainter *painter)
{
    painter->setFont(m_vectorSettings.m_layout.getLabelFont(painter)); // for reproducability

    VectorPixAtomicsPainter::drawCoordCross(painter, m_vectorSettings.m_layout);
    VectorPixAtomicsPainter::drawCircle(painter, m_vectorSettings.m_lengths, m_vectorSettings.m_layout);

    constexpr int dark = 130;
    QVector<QColor> colors{QColor("black"), QColor("red").darker(dark), QColor("red").darker(dark)};
    QStringList labels = QStringList() <<
                         "UL1" <<
                         "UL2" <<
                         "UL3" <<
                         "IL1" <<
                         "IL2" <<
                         "IL3" <<
                         "UL1-UL2" <<
                         "UL3-UL2" <<
                         "Van" <<
                         "Vbn" <<
                         "Vcn" <<
                         "Ia";
    for (int i=1; i<=12; ++i) {
        float angle = degToRad(float(i) * 360.0 / 12);
        QColor color = colors[i % colors.count()];
        QString label = labels[i % labels.count()];

        std::complex<double> corner = std::polar<double>(vectorLen, angle);
        QVector2D value = QVector2D(corner.real(),corner.imag());
        QVector2D vectorPixLen = VectorPaintCalc::calcPixVec(painter, { m_vectorSettings, PhaseType::TYPE_U}, value);

        VectorPixAtomicsPainter::drawLabel(painter,
                                           { PhaseType::TYPE_U, vectorPixLen, color },
                                           m_vectorSettings.m_layout.getLabelFont(painter),
                                           label);
        // Test for our text metrics aproximization. Dot should be in center of label
        const float dotWidth = 3;
        painter->setPen(QPen(Qt::blue, dotWidth));
        const float centerX = VectorPaintCalc::centerX(painter);
        const float centerY = VectorPaintCalc::centerY(painter);
        QPointF positionCenter(centerX + vectorPixLen.x(), centerY + vectorPixLen.y());
        painter->drawPoint(positionCenter);
    }
}
