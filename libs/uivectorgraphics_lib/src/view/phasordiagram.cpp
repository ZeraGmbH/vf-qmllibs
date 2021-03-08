#include "phasordiagram.h"
#include <QGradient>


//used for atan2 and math constants like M_PI
#include <math.h>

// HelloItemPainter contains the painting code

static constexpr float LABEL_ROTATE_ANGLE =  -25.0 * M_PI/180;

float PhasorDiagram::pixelScale(float t_base)
{
    return std::min(height(), width())/t_base/2;
}

void PhasorDiagram::drawLabel(QPainter *t_painter, const QString &t_label, float t_vectorPhi, QColor t_color, float t_scale, float t_labelPhiOffset)
{
    float xOffset = t_label.length()*5;
    const float tmpPhi = t_vectorPhi - m_phiOrigin;
    float xPos = m_fromX - xOffset + t_scale * m_gridScale * m_circleValue * 1.2 * cos(tmpPhi + t_labelPhiOffset);
    float yPos = m_fromY + 5 + 0.9 * t_scale * m_gridScale * m_circleValue * 1.2 * sin(tmpPhi + t_labelPhiOffset);

    t_painter->setPen(QPen(t_color, 2));
    t_painter->setFont(m_defaultFont);
    t_painter->drawText(round(xPos), round(yPos),t_label);
}

void PhasorDiagram::drawArrowHead(QPainter *t_painter, QVector2D t_vector, QColor t_color, float t_maxValue)
{
    t_painter->setPen(QPen(t_color, 2));
    float arrowHeadSize = height() / 35;

    const float tmpPhi = atan2(t_vector.y(), t_vector.x()) - m_phiOrigin;
    const float tmpToX = m_fromX + pixelScale(t_maxValue) * t_vector.length() * cos(tmpPhi);
    const float tmpToY = m_fromY + pixelScale(t_maxValue) * t_vector.length() * sin(tmpPhi);

    const float angle = atan2(tmpToY - m_fromY , tmpToX - m_fromX);
    if((pixelScale(t_maxValue) * t_vector.length()) != 0){
        QVector<QPoint> points = {
            QPoint(tmpToX, tmpToY),
            QPoint(tmpToX - arrowHeadSize * cos(angle - M_PI / 6),tmpToY - arrowHeadSize * sin(angle - M_PI / 6)),
            QPoint(tmpToX - arrowHeadSize * cos(angle + M_PI / 6), tmpToY - arrowHeadSize * sin(angle + M_PI / 6)),
        };

        QPolygon poly(points);

        t_painter->drawPolygon(poly);

        QBrush brush;
        brush.setColor(t_color);
        brush.setStyle(Qt::SolidPattern);

        QPainterPath path;
        path.addPolygon(poly);

        t_painter->fillPath(path, brush);
    }
}

void PhasorDiagram::drawVectorLine(QPainter *t_painter, QVector2D t_vector, QColor t_color, float t_maxValue)
{
    t_painter->setPen(QPen(t_color, 2));
    const float tmpPhi = atan2(t_vector.y(), t_vector.x()) - m_phiOrigin;
    const float tmpX = m_fromX + pixelScale(t_maxValue) * t_vector.length() * cos(tmpPhi);
    const float tmpY = m_fromY + pixelScale(t_maxValue) * t_vector.length() * sin(tmpPhi);
    t_painter->drawLine(m_fromX, m_fromY, tmpX, tmpY);
}

void PhasorDiagram::drawVectors(QPainter *t_painter, bool drawVoltages, bool drawCurrents, float t_voltageFactor)
{
    // To get a nice experience, vectors are drawn in the sequence of their
    // visible lengths: Long vectors first / short vectors last
    // To accomplish, we use QMultiMap with key containing visible length
    struct TVectorData {
        TVectorData(QVector2D vector,
                    QColor colour,
                    float maxVal,
                    float factorVal,
                    bool drawLabel,
                    QString label,
                    float labelPositionScale,
                    float labelPhiOffset) {
            this->vector = vector;
            this->colour = colour;
            this->maxVal = maxVal;
            this->factorVal = factorVal;
            this->drawLabel = drawLabel;
            this->label = label;
            this->labelPositionScale = labelPositionScale;
            this->labelPhiOffset = labelPhiOffset;
        }

        QVector2D vector;
        QColor colour;
        float maxVal;
        float factorVal;
        bool drawLabel;
        QString label;
        float labelPositionScale;
        float labelPhiOffset;
    };
    QMultiMap<float, TVectorData> sortedVectors;

    QVector2D vectorUScreen[3];
    QVector2D vectorIScreen[3];

    // add voltages sorted
    if(drawVoltages) {
        QVector2D vectors[] = { m_vector1, m_vector2, m_vector3 };
        QColor colors[] = { m_vector1Color, m_vector2Color, m_vector3Color };
        QString labels[] = { m_vector1Label, m_vector2Label, m_vector3Label };
        for(int idx = 0; idx < 3; ++idx) {
            QVector2D vector = vectors[idx];
            vectorUScreen[idx] = vector / (m_maxVoltage * t_voltageFactor);
            QString label = labels[idx];
            if(vector.length() > m_minVoltage * t_voltageFactor) {
                float screenLen = vectorUScreen[idx].length();
                TVectorData currVectorData(vector,
                                           colors[idx],
                                           m_maxVoltage,
                                           t_voltageFactor,
                                           !label.isEmpty() && vector.length() > m_maxVoltage * t_voltageFactor / 10,
                                           label,
                                           labelVectorLen(screenLen),
                                           (1-screenLen)*LABEL_ROTATE_ANGLE);
                // negative len for long -> short order
                sortedVectors.insert(-screenLen, currVectorData);
            }
        }
    }
    // add currents sorted
    if(drawCurrents) {
        QVector2D vectors[] = { m_vector4, m_vector5, m_vector6 };
        QColor colors[] = { m_vector4Color, m_vector5Color, m_vector6Color };
        QString labels[] = { m_vector4Label, m_vector5Label, m_vector6Label };
        for(int idx = 0; idx < 3; ++idx) {
            QVector2D vector = vectors[idx];
            vectorIScreen[idx] = vector / m_maxCurrent;
            QString label = labels[idx];
            if(vector.length() > m_minCurrent) {
                float screenLen = vectorIScreen[idx].length();
                TVectorData currVectorData(vector,
                                           colors[idx],
                                           m_maxCurrent,
                                           1.0,
                                           !label.isEmpty() && vector.length() > m_maxCurrent / 10,
                                           label,
                                           labelVectorLen(screenLen),
                                           (screenLen-1)*LABEL_ROTATE_ANGLE);
                // In case we have identical vectors for current and voltage:
                // display voltage topmost
                float lenUPreferFactor = 1.0;
                if(drawVoltages) {
                    for(int uidx = 0; uidx<3; ++uidx) {
                        if(vectorIScreen[idx].distanceToPoint(vectorUScreen[uidx]) < 0.02) {
                            lenUPreferFactor = 1.02;
                            break;
                        }
                    }
                }

                // negative len for long -> short order
                sortedVectors.insert(-screenLen*lenUPreferFactor, currVectorData);
            }
        }
    }
    // draw sorted long -> short
    for(auto vData : sortedVectors) {
        drawArrowHead(t_painter, vData.vector, vData.colour, vData.maxVal * vData.factorVal);
        drawVectorLine(t_painter, vData.vector, vData.colour, vData.maxVal * vData.factorVal);
        if(vData.drawLabel) {
            drawLabel(t_painter, vData.label, atan2(vData.vector.y(), vData.vector.x()), vData.colour, vData.labelPositionScale, vData.labelPhiOffset);
        }
    }
}

void PhasorDiagram::drawTriangle(QPainter *t_painter)
{
    //Scale vectors and convert to x/y
    //v1
    const float v1Phi = atan2(m_vector1.y(), m_vector1.x()) - m_phiOrigin;
    const float v1X = m_fromX + m_gridScale * m_vector1.length() * cos(v1Phi);
    const float v1Y = m_fromY + m_gridScale * m_vector1.length() * sin(v1Phi);

    //v2
    const float v2Phi = atan2(m_vector2.y(), m_vector2.x()) - m_phiOrigin;
    const float v2X = m_fromX + m_gridScale * m_vector2.length() * cos(v2Phi);
    const float v2Y = m_fromY + m_gridScale * m_vector2.length() * sin(v2Phi);

    //v3
    const float v3Phi = atan2(m_vector3.y(), m_vector3.x()) - m_phiOrigin;
    const float v3X = m_fromX + m_gridScale * m_vector3.length() * cos(v3Phi);
    const float v3Y = m_fromY + m_gridScale * m_vector3.length() * sin(v3Phi);

    //Gradients
    //v1->v2
    QLinearGradient grd1(QPoint(v1X, v1Y), QPoint(v2X, v2Y));
    grd1.setColorAt(0,m_vector1Color);
    grd1.setColorAt(1,m_vector2Color);

    //v2->v3
    QLinearGradient grd2(QPoint(v2X, v2Y), QPoint(v3X, v3Y));
    grd2.setColorAt(0,m_vector2Color);
    grd2.setColorAt(1,m_vector3Color);

    //v3->v1
    QLinearGradient grd3(QPoint(v3X, v3Y), QPoint(v1X, v1Y));
    grd3.setColorAt(0,m_vector3Color);
    grd3.setColorAt(1,m_vector1Color);

    //--Draw--//////////////////////// v1 -> v2
    t_painter->setPen(QPen(grd1, 2));
    t_painter->drawLine(v1X, v1Y,v2X, v2Y);

    //--Draw--//////////////////////// v2 -> v3
    t_painter->setPen(QPen(grd2, 2));
    t_painter->drawLine(v2X, v2Y,v3X, v3Y);

    //--Draw--//////////////////////// v3 -> v1
    t_painter->setPen(QPen(grd3, 2));
    t_painter->drawLine(v3X, v3Y,v1X, v1Y);


    if(m_vector1Label.isEmpty() == false && m_vector1.length() > m_maxVoltage / 10) {
        QVector2D vectorUScreen = m_vector1 / m_maxVoltage;
        float screenLen = vectorUScreen.length();
        drawLabel(t_painter, m_vector1Label, atan2(m_vector1.y(), m_vector1.x()), m_vector1Color,
                  labelVectorLen(screenLen),
                  (1-screenLen)*LABEL_ROTATE_ANGLE);
    }

    if(m_vector2Label.isEmpty() == false && m_vector2.length() > m_maxVoltage / 10) {
        QVector2D vectorUScreen = m_vector2 / m_maxVoltage;
        float screenLen = vectorUScreen.length();
        drawLabel(t_painter, m_vector2Label, atan2(m_vector2.y(), m_vector2.x()), m_vector2Color,
                  labelVectorLen(screenLen),
                  (1-screenLen)*LABEL_ROTATE_ANGLE);
    }

    if(m_vector3Label.isEmpty() == false && m_vector3.length() > m_maxVoltage / 10) {
        QVector2D vectorUScreen = m_vector3 / m_maxVoltage;
        float screenLen = vectorUScreen.length();
        drawLabel(t_painter, m_vector3Label, atan2(m_vector3.y(), m_vector3.x()), m_vector3Color,
                  labelVectorLen(screenLen),
                  (1-screenLen)*LABEL_ROTATE_ANGLE);
    }
}

void PhasorDiagram::drawGridAndCircle(QPainter *t_painter)
{
    t_painter->setPen(QPen(Qt::gray, 1));

    //grid
    if(m_gridVisible) {
        //x axis
        t_painter->drawLine(m_fromX - m_maxVoltage * m_gridScale, m_fromY, m_fromX + m_maxVoltage * m_gridScale, m_fromY);

        //y axis
        t_painter->drawLine(m_fromX, m_fromY - m_maxVoltage * m_gridScale, m_fromX, m_fromY + m_maxVoltage * m_gridScale);
    }

    //circle
    if(m_circleVisible) {
        t_painter->drawArc(m_fromX-(m_gridScale * m_circleValue), m_fromY-(m_gridScale * m_circleValue),2 * m_gridScale * m_circleValue,2 * m_gridScale * m_circleValue, 0, 5760);
    }
}

float PhasorDiagram::labelVectorLen(float screenLen)
{
    return screenLen*1.25 > 1.1 ? 1.1 : screenLen*1.25;
}

void PhasorDiagram::synchronize(QQuickItem *t_item)
{
    PhasorDiagram *realItem  = static_cast<PhasorDiagram *>(t_item);
    Q_ASSERT(realItem != nullptr);

    m_fromX = realItem->fromX();
    m_fromY = realItem->fromY();
    m_phiOrigin = realItem->phiOrigin();
    m_gridScale = realItem->gridScale();
    m_minVoltage = realItem->minVoltage();
    m_maxVoltage = realItem->maxVoltage();
    m_minCurrent = realItem->minCurrent();
    m_maxCurrent = realItem->maxCurrent();
    m_currentVisible = realItem->currentVisible();
    m_vectorView = realItem->vectorView();
    m_vectorMode = realItem->vectorMode();
    m_gridVisible = realItem->gridVisible();
    m_gridColor = realItem->gridColor();
    m_circleVisible = realItem->circleVisible();
    m_circleColor = realItem->circleColor();
    m_circleValue = realItem->circleValue();

    m_vector1Color = realItem->vector1Color();
    m_vector2Color = realItem->vector2Color();
    m_vector3Color = realItem->vector3Color();
    m_vector4Color = realItem->vector4Color();
    m_vector5Color = realItem->vector5Color();
    m_vector6Color = realItem->vector6Color();

    m_vector1Label = realItem->vector1Label();
    m_vector2Label = realItem->vector2Label();
    m_vector3Label = realItem->vector3Label();
    m_vector4Label = realItem->vector4Label();
    m_vector5Label = realItem->vector5Label();
    m_vector6Label = realItem->vector6Label();

    QList<double> tmpData = realItem->vector1Data();
    if(tmpData.length() > 1) {
        m_vector1 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
    tmpData = realItem->vector2Data();
    if(tmpData.length() > 1) {
        m_vector2 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
    tmpData = realItem->vector3Data();
    if(tmpData.length() > 1) {
        m_vector3 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
    tmpData = realItem->vector4Data();
    if(tmpData.length() > 1) {
        m_vector4 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
    tmpData = realItem->vector5Data();
    if(tmpData.length() > 1) {
        m_vector5 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
    tmpData = realItem->vector6Data();
    if(tmpData.length() > 1) {
        m_vector6 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
}


PhasorDiagram::PhasorDiagram(QQuickItem *t_parent) : QQuickPaintedItem(t_parent)
{
    m_vector1Data.append(10);
    m_vector1Data.append(20);
}


void PhasorDiagram::paint(QPainter *t_painter)
{
    synchronize((QQuickItem*)this);
    m_defaultFont.setPixelSize(height() / 25);
    drawGridAndCircle(t_painter);

    switch(m_vectorView)
    {
    case PhasorDiagram::VectorView::VIEW_STAR:
        drawVectors(t_painter, true, m_currentVisible);
        break;
    case PhasorDiagram::VectorView::VIEW_TRIANGLE:
        drawTriangle(t_painter);
        drawVectors(t_painter, false, m_currentVisible);
        break;
    case PhasorDiagram::VectorView::VIEW_THREE_PHASE:
        drawVectors(t_painter, true, m_currentVisible, sqrt(3.0f)/*concatenated voltage */);
        break;
    }
}
