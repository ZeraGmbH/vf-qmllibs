#include "testprimitivepainterlabel.h"
#include "vectorpaintcalc.h"
#include "vectorprimitivespainter.h"
#include <QVector2D>
#include <complex>

constexpr float vectorLen = 1.0;

TestPrimitivePainterLabel::TestPrimitivePainterLabel()
{
    m_settingsGeometry.m_lengths.setNomVoltage(vectorLen);
    m_settingsGeometry.m_lengths.setNomCurrent(vectorLen);
    m_settingsGeometry.m_angles.setRotationDirection(VectorSettingsAngles::Clockwise);
    m_settingsGeometry.m_angles.setOffsetAngle(degToRad(-90));
}

void TestPrimitivePainterLabel::paint(QPainter *painter)
{
    painter->setFont(VectorSettingsStatic::getDefaultFont(painter)); // for reproducability

    QColor circleCoordColor("grey");
    const float coordCircleLineWidth = VectorSettingsStatic::getCoordCrossAndCircleLineWidth(painter);
    VectorPrimitivesPainter::drawCoordCross(painter, circleCoordColor, coordCircleLineWidth);
    VectorPrimitivesPainter::drawCircle(painter, m_settingsGeometry.m_lengths, circleCoordColor, coordCircleLineWidth);

    constexpr int dark = 130;
    QVector<QColor> colors{QColor("black"), QColor("red").darker(dark), QColor("red").darker(dark)};
    QStringList labels = QStringList() <<
                         "TWELVE" <<
                         "one" <<
                         "two" <<
                         "THREE" <<
                         "four" <<
                         "five" <<
                         "SIX" <<
                         "seven" <<
                         "eight" <<
                         "NINE" <<
                         "ten" <<
                         "eleven";
    for (int i=1; i<=12; ++i) {
        float angle = degToRad(float(i) * 360.0 / 12);
        QColor color = colors[i % colors.count()];
        QString label = labels[i % labels.count()];

        std::complex<double> corner = std::polar<double>(vectorLen, angle);
        QVector2D value = QVector2D(corner.real(),corner.imag());
        QVector2D vectorPixLen = VectorPaintCalc::calcPixVec(painter, { m_settingsGeometry, VectorSettingsStatic::TYPE_U}, value);

        VectorPrimitivesPainter::drawLabel(painter,
                                           { vectorPixLen, color },
                                           label);
        // Test for our text metrics aproximization. Dot should be in center of label
        const float dotWidth = 16;
        painter->setPen(QPen(Qt::blue, dotWidth));
        const float centerX = VectorPaintCalc::centerX(painter);
        const float centerY = VectorPaintCalc::centerY(painter);
        QPointF positionCenter(centerX + vectorPixLen.x(), centerY + vectorPixLen.y());
        painter->drawPoint(positionCenter);
    }
}
