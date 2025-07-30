#include "vectorpainter.h"
#include <QGradient>
#include <QPainterPath>
#include <QMultiMap>
#include <math.h>

void VectorPainter::setPhiOrigin(const float &phiOrigin)
{
    m_phiOrigin = phiOrigin;
}

void VectorPainter::setGridScale(float gridScale)
{
    m_gridScale = gridScale;
}

void VectorPainter::setMaxVoltage(float maxVoltage)
{
    m_maxVoltage = maxVoltage;
}

void VectorPainter::setMinVoltage(float minVoltage)
{
    m_minVoltage = minVoltage;
}

void VectorPainter::setMaxCurrent(float maxCurrent)
{
    m_maxCurrent = maxCurrent;
}

void VectorPainter::setMinCurrent(float minCurrent)
{
    m_minCurrent = minCurrent;
}

void VectorPainter::setVectorView(VectorView vectorView)
{
    m_vectorView = vectorView;
}

void VectorPainter::setMaxValueVoltage(float maxValueVoltage)
{
    m_maxValueVoltage = maxValueVoltage;
}

void VectorPainter::setMaxValueCurrent(float maxValueCurrent)
{
    m_maxValueCurrent = maxValueCurrent;
}

void VectorPainter::setGridVisible(bool gridVisible)
{
    m_gridVisible = gridVisible;
}

void VectorPainter::setGridColor(const QColor &gridColor)
{
    m_gridColor = gridColor;
}

void VectorPainter::setCircleVisible(bool circleVisible)
{
    m_circleVisible = circleVisible;
}

void VectorPainter::setCircleColor(const QColor &circleColor)
{
    m_circleColor = circleColor;
}

void VectorPainter::setCircleValue(float circleValue)
{
    m_circleValue = circleValue;
}

void VectorPainter::setForceI1Top(bool forceI1Top)
{
    m_forceI1Top = forceI1Top;
}

void VectorPainter::setVector(int idx, const QVector2D &vector)
{
    m_vector[idx] = vector;
}

void VectorPainter::setVectorColor(int idx, const QColor &vectorColor)
{
    m_vectorColor[idx] = vectorColor;
}

void VectorPainter::setVectorLabel(int idx, const QString &vectorLabel)
{
    m_vectorLabel[idx] = vectorLabel;
}

void VectorPainter::paint(QPainter *painter)
{
    m_SetUCollisions.clear();
    m_fromX = painter->device()->width() / 2;
    m_fromY = painter->device()->height() / 2;
    m_defaultFont.setPixelSize(height(painter) > 0.0 ? height(painter) / 25 : 10.0);

    drawGridAndCircle(painter);

    constexpr float LABEL_ROTATE_ANGLE =  -6.0 * M_PI / 180;
    // 3ph display has longer texts (e.g 'UL1-UL2') so needs to rotate more
    constexpr float LABEL_ROTATE_ANGLE_3PH_U =  -30.0 * M_PI / 180;
    constexpr float LABEL_ROTATE_ANGLE_3PH_I =  -5.0 * M_PI / 180;

    switch(m_vectorView)
    {
    case VectorView::VIEW_STAR:
        m_currLabelRotateAngleU = LABEL_ROTATE_ANGLE;
        m_currLabelRotateAngleI = LABEL_ROTATE_ANGLE;
        drawVectors(painter, true, true);
        break;
    case VectorView::VIEW_TRIANGLE:
        m_currLabelRotateAngleU = LABEL_ROTATE_ANGLE;
        m_currLabelRotateAngleI = LABEL_ROTATE_ANGLE;
        drawTriangle(painter);
        drawVectors(painter, false, true);
        break;
    case VectorView::VIEW_THREE_PHASE:
        m_currLabelRotateAngleU = LABEL_ROTATE_ANGLE_3PH_U;
        m_currLabelRotateAngleI = LABEL_ROTATE_ANGLE_3PH_I;
        drawVectors(painter, true, true, sqrt(3.0f)/*concatenated voltage */);
        break;
    }
}

float VectorPainter::pixelScale(QPainter *painter, float base)
{
    return std::min(height(painter), width(painter))/base/2;
}

void VectorPainter::drawCenterPoint(QPainter *painter)
{
    painter->setPen(QPen(Qt::gray, 2));
    painter->drawPoint(m_fromX, m_fromY);
}

void VectorPainter::drawLabel(QPainter *painter,
                              int idx,
                              const QFont &font,
                              float scale,
                              float labelPhiOffset)
{
    QFontMetrics fontMetrics(font);
    const QString& label = m_vectorLabel[idx];
    int xOffset = fontMetrics.horizontalAdvance(label) / 2;

    const float vectorPhi = atan2(m_vector[idx].y(), m_vector[idx].x());
    const float tmpPhi = vectorPhi - m_phiOrigin;
    constexpr float maxPhi = 0.25;
    if(fabs(labelPhiOffset) > maxPhi) {
        if(labelPhiOffset > 0)
            labelPhiOffset = maxPhi;
        else
            labelPhiOffset = -maxPhi;
    }
    float xPos = m_fromX - xOffset + scale * m_gridScale * m_circleValue * 1.2 * cos(tmpPhi + labelPhiOffset);
    float yPos = m_fromY + 5 + 0.9 * scale * m_gridScale * m_circleValue * 1.2 * sin(tmpPhi + labelPhiOffset);

    painter->setPen(QPen(m_vectorColor[idx], 2));
    painter->setFont(font);
    painter->drawText(round(xPos), round(yPos), label);
}

void VectorPainter::drawArrowHead(QPainter *painter, int idx, float maxValue)
{
    const QColor &color = m_vectorColor[idx];
    painter->setPen(QPen(color, 2));
    float arrowHeadSize = height(painter) / 35;

    const QVector2D vector = m_vector[idx];
    const float tmpPhi = atan2(vector.y(), vector.x()) - m_phiOrigin;
    const float tmpToX = m_fromX + pixelScale(painter, maxValue) * vector.length() * cos(tmpPhi);
    const float tmpToY = m_fromY + pixelScale(painter, maxValue) * vector.length() * sin(tmpPhi);

    const float angle = atan2(tmpToY - m_fromY , tmpToX - m_fromX);
    if((pixelScale(painter, maxValue) * vector.length()) != 0){
        QVector<QPoint> points = {
            QPoint(roundf(tmpToX), roundf(tmpToY)),
            QPoint(roundf(tmpToX - arrowHeadSize * cos(angle - M_PI / 8)), roundf(tmpToY - arrowHeadSize * sin(angle - M_PI / 8))),
            QPoint(roundf(tmpToX - arrowHeadSize * cos(angle + M_PI / 8)), roundf(tmpToY - arrowHeadSize * sin(angle + M_PI / 8))),
        };

        QPolygon poly(points);
        painter->drawPolygon(poly);

        QBrush brush;
        brush.setColor(color);
        brush.setStyle(Qt::SolidPattern);

        QPainterPath path;
        path.addPolygon(poly);

        painter->fillPath(path, brush);
    }
}

void VectorPainter::drawTriangle(QPainter *painter)
{
    //Scale vectors and convert to x/y
    //v1
    const float v1Phi = atan2(m_vector[0].y(), m_vector[0].x()) - m_phiOrigin;
    const float v1X = m_fromX + m_gridScale * m_vector[0].length() * cos(v1Phi);
    const float v1Y = m_fromY + m_gridScale * m_vector[0].length() * sin(v1Phi);

    //v2
    const float v2Phi = atan2(m_vector[1].y(), m_vector[1].x()) - m_phiOrigin;
    const float v2X = m_fromX + m_gridScale * m_vector[1].length() * cos(v2Phi);
    const float v2Y = m_fromY + m_gridScale * m_vector[1].length() * sin(v2Phi);

    //v3
    const float v3Phi = atan2(m_vector[2].y(), m_vector[2].x()) - m_phiOrigin;
    const float v3X = m_fromX + m_gridScale * m_vector[2].length() * cos(v3Phi);
    const float v3Y = m_fromY + m_gridScale * m_vector[2].length() * sin(v3Phi);

    //Gradients
    //v1->v2
    QLinearGradient grd1(QPoint(v1X, v1Y), QPoint(v2X, v2Y));
    grd1.setColorAt(0,m_vectorColor[0]);
    grd1.setColorAt(1,m_vectorColor[1]);

    //v2->v3
    QLinearGradient grd2(QPoint(v2X, v2Y), QPoint(v3X, v3Y));
    grd2.setColorAt(0,m_vectorColor[1]);
    grd2.setColorAt(1,m_vectorColor[2]);

    //v3->v1
    QLinearGradient grd3(QPoint(v3X, v3Y), QPoint(v1X, v1Y));
    grd3.setColorAt(0,m_vectorColor[2]);
    grd3.setColorAt(1,m_vectorColor[0]);

    //--Draw--//////////////////////// v1 -> v2
    painter->setPen(QPen(grd1, 2));
    painter->drawLine(v1X, v1Y,v2X, v2Y);

    //--Draw--//////////////////////// v2 -> v3
    painter->setPen(QPen(grd2, 2));
    painter->drawLine(v2X, v2Y,v3X, v3Y);

    //--Draw--//////////////////////// v3 -> v1
    painter->setPen(QPen(grd3, 2));
    painter->drawLine(v3X, v3Y,v1X, v1Y);

    if(m_vectorLabel[0].isEmpty() == false && m_vector[0].length() > m_maxVoltage / 10) {
        m_vectorUScreen[0] = m_vector[0] / m_maxVoltage;
        float screenLenLabel = m_vectorUScreen[0].length();
        drawLabel(
            painter,
            0,
            m_defaultFont,
            labelVectorLen(screenLenLabel),
            (1/screenLenLabel)*m_currLabelRotateAngleU*detectCollision(0));
    }

    if(m_vectorLabel[1].isEmpty() == false && m_vector[1].length() > m_maxVoltage / 10) {
        m_vectorUScreen[1] = m_vector[1] / m_maxVoltage;
        float screenLenLabel = m_vectorUScreen[1].length();
        drawLabel(
            painter,
            1,
            m_defaultFont,
            labelVectorLen(screenLenLabel),
            (1/screenLenLabel)*m_currLabelRotateAngleU*detectCollision(1));
    }

    if(m_vectorLabel[2].isEmpty() == false && m_vector[2].length() > m_maxVoltage / 10) {
        m_vectorUScreen[2] = m_vector[2] / m_maxVoltage;
        float screenLenLabel = m_vectorUScreen[2].length();
        drawLabel(
            painter,
            2,
            m_defaultFont,
            labelVectorLen(screenLenLabel),
            (1/screenLenLabel)*m_currLabelRotateAngleU*detectCollision(2));
    }
}

float VectorPainter::labelVectorLen(float screenLen)
{
    // limit labels out of range
    float labelLen = screenLen * 1.25;
    if(labelLen > 1.1)
        return 1.1;
    // avoid crowded center
    if(labelLen < 0.4)
        return 0.4;
    return labelLen;
}

float VectorPainter::detectCollision(int uPhase)
{
    // check collision with I vectors
    QVector2D vectors[] = { m_vector[3], m_vector[4], m_vector[5] };
    for(int idx = 0; idx<COUNT_PHASES; ++idx) {
        QVector2D vectorI = vectors[idx];
        // compare angles
        QVector2D vectorIScreen = vectorI / m_maxCurrent;
        QVector2D vectorUScreen = m_vectorUScreen[uPhase];
        float angleI = atan2(vectorIScreen.y() , vectorIScreen.x());
        float angleU = atan2(vectorUScreen.y() , vectorUScreen.x());
        float diffAngle = fabs(angleU - angleI);
        if(angleU > angleI && diffAngle < 0.7) {
            m_SetUCollisions.insert(idx);
            return -1.0;
        }
    }
    return 1.0;
}

void VectorPainter::drawGridAndCircle(QPainter *painter)
{
    constexpr double radiusWidth = 1.5;
    //grid
    if(m_gridVisible) {
        painter->setPen(QPen(m_gridColor, radiusWidth));
        //x axis
        painter->drawLine(m_fromX - m_maxVoltage * m_gridScale, m_fromY, m_fromX + m_maxVoltage * m_gridScale, m_fromY);

        //y axis
        painter->drawLine(m_fromX, m_fromY - m_maxVoltage * m_gridScale, m_fromX, m_fromY + m_maxVoltage * m_gridScale);
    }

    //circle
    if(m_circleVisible) {
        painter->setPen(QPen(m_circleColor, radiusWidth));
        painter->drawArc(
            m_fromX-(m_gridScale * m_circleValue)-radiusWidth,
            m_fromY-(m_gridScale * m_circleValue)-radiusWidth,
            2 * (m_gridScale * m_circleValue + radiusWidth),
            2 * (m_gridScale * m_circleValue + radiusWidth),
            0, 5760);
    }
}

void VectorPainter::drawVectors(QPainter *painter, bool drawVoltages, bool drawCurrents, float voltageFactor)
{
    // To get a nice experience, vectors are drawn in the sequence of their
    // visible lengths: Long vectors first / short vectors last
    // To accomplish, we use QMultiMap with key containing visible length
    struct TVectorData {
        TVectorData(int idx,
                    float maxVal,
                    float factorVal,
                    float labelPositionScale,
                    float labelPhiOffset) {
            this->idx = idx;
            this->maxVal = maxVal;
            this->factorVal = factorVal;
            this->labelPositionScale = labelPositionScale;
            this->labelPhiOffset = labelPhiOffset;
        }
        int idx;
        float maxVal;
        float factorVal;
        float labelPositionScale;
        float labelPhiOffset;
    };
    QMultiMap<float, TVectorData> sortedVectors;

    // add voltages sorted
    if(drawVoltages) {
        QVector2D vectors[] = { m_vector[0], m_vector[1], m_vector[2] };
        for(int idx = 0; idx < COUNT_PHASES; ++idx) {
            QVector2D vector = vectors[idx];
            m_vectorUScreen[idx] = vector / (m_maxVoltage * voltageFactor);
            if(vector.length() > m_minVoltage * voltageFactor) {
                float screenLenVector = m_vectorUScreen[idx].length();
                TVectorData currVectorData(idx,
                                           m_maxVoltage,
                                           voltageFactor,
                                           labelVectorLen(screenLenVector),
                                           (1/screenLenVector)*m_currLabelRotateAngleU * detectCollision(idx));
                // negative len for long -> short order
                sortedVectors.insert(-screenLenVector, currVectorData);
            }
        }
    }
    // add currents sorted
    if(drawCurrents) {
        QVector2D vectors[] = { m_vector[3], m_vector[4], m_vector[5] };
        for(int idx = 0; idx < COUNT_PHASES; ++idx) {
            QVector2D vector = vectors[idx];
            QVector2D vectorIScreen = vector / m_maxCurrent;
            if(vector.length() > m_minCurrent) {
                float screenLenVectorI = vectorIScreen.length();
                float labelRotateAngleI = (-1/screenLenVectorI)*m_currLabelRotateAngleI;
                if(m_SetUCollisions.contains(idx)) {
                    labelRotateAngleI = -labelRotateAngleI;
                }
                TVectorData currVectorData(idx+COUNT_PHASES,
                                           m_maxCurrent,
                                           1.0,
                                           labelVectorLen(screenLenVectorI),
                                           labelRotateAngleI);
                // In case we have identical vectors for current and voltage:
                // display voltage topmost
                float lenUPreferFactor = 1.0;
                if(drawVoltages) {
                    for(int uidx = 0; uidx<COUNT_PHASES; ++uidx) {
                        if(vectorIScreen.distanceToPoint(m_vectorUScreen[uidx]) < 0.02) {
                            if(!m_forceI1Top || (uidx == 0 && idx == 0) || idx != 0) {
                                lenUPreferFactor = 1.02;
                            }
                            else {
                                lenUPreferFactor = 0.98;
                            }
                            break;
                        }
                    }
                }

                // negative len for long -> short order
                sortedVectors.insert(-screenLenVectorI*lenUPreferFactor, currVectorData);
            }
        }
    }
    // draw sorted long -> short
    for(const TVectorData &vData : sortedVectors) {
        drawArrowHead(painter, vData.idx, vData.maxVal * vData.factorVal);
        drawVectorLine(painter, vData.idx, vData.maxVal * vData.factorVal);
        drawLabel(painter,
                  vData.idx,
                  m_defaultFont,
                  vData.labelPositionScale,
                  vData.labelPhiOffset);
    }

    // do not leave center on random colour
    if(sortedVectors.count() >1)
        drawCenterPoint(painter);
}

void VectorPainter::drawVectorLine(QPainter *painter, int idx, float maxValue)
{
    painter->setPen(QPen(m_vectorColor[idx], 2));
    const QVector2D vector = m_vector[idx];
    const float tmpPhi = atan2(vector.y(), vector.x()) - m_phiOrigin;
    const float tmpX = m_fromX + pixelScale(painter, maxValue) * vector.length() * cos(tmpPhi);
    const float tmpY = m_fromY + pixelScale(painter, maxValue) * vector.length() * sin(tmpPhi);
    painter->drawLine(roundf(m_fromX), roundf(m_fromY), roundf(tmpX), roundf(tmpY));
}

int VectorPainter::height(QPainter *painter)
{
    QPaintDevice *paintDevice = painter->device();
    if (paintDevice)
        return paintDevice->height();
    return 1;
}

int VectorPainter::width(QPainter *painter)
{
    QPaintDevice *paintDevice = painter->device();
    if (paintDevice)
        return paintDevice->width();
    return 1;
}

