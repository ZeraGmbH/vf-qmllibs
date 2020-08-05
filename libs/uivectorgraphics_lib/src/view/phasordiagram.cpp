#include "phasordiagram.h"
#include <QGradient>


//used for atan2 and math constants like M_PI
#include <math.h>

// HelloItemPainter contains the painting code

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
    float arrowHeadSize = 12.0f;

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

void PhasorDiagram::drawVoltageArrows(QPainter *t_painter, float t_factor)
{
    m_defaultFont.setPixelSize(20);

    drawArrowHead(t_painter, m_vector1, m_vector1Color, m_maxVoltage * t_factor);
    drawVectorLine(t_painter, m_vector1, m_vector1Color, m_maxVoltage * t_factor);
    if(m_vector1Label.isEmpty() == false && m_vector1.length() > m_maxVoltage * t_factor / 10)
    {
        drawLabel(t_painter, m_vector1Label, atan2(m_vector1.y(), m_vector1.x()), m_vector1Color);
    }

    drawArrowHead(t_painter, m_vector2, m_vector2Color, m_maxVoltage * t_factor);
    drawVectorLine(t_painter, m_vector2, m_vector2Color, m_maxVoltage * t_factor);
    if(m_vector2Label.isEmpty() == false && m_vector2.length() > m_maxVoltage * t_factor / 10)
    {
        drawLabel(t_painter, m_vector2Label, atan2(m_vector2.y(), m_vector2.x()), m_vector2Color);
    }

    drawArrowHead(t_painter, m_vector3, m_vector3Color, m_maxVoltage * t_factor);
    drawVectorLine(t_painter, m_vector3, m_vector3Color, m_maxVoltage * t_factor);
    if(m_vector3Label.isEmpty() == false && m_vector3.length() > m_maxVoltage * t_factor / 10)
    {
        drawLabel(t_painter, m_vector3Label, atan2(m_vector3.y(), m_vector3.x()), m_vector3Color);
    }
}

void PhasorDiagram::drawCurrentArrows(QPainter *t_painter)
{
    if(m_currentVisible)
    {
        drawVectorLine(t_painter, m_vector4, m_vector4Color, m_maxCurrent);
        drawArrowHead(t_painter, m_vector4, m_vector4Color, m_maxCurrent);
        if(m_vector4Label.isEmpty() == false && m_vector4.length() > m_maxCurrent / 10)
        {
            drawLabel(t_painter, m_vector4Label, atan2(m_vector4.y(), m_vector4.x()), m_vector4Color, 0.5, m_labelPhiOffset);
        }

        drawVectorLine(t_painter, m_vector5, m_vector5Color, m_maxCurrent);
        drawArrowHead(t_painter, m_vector5, m_vector5Color, m_maxCurrent);
        if(m_vector5Label.isEmpty() == false && m_vector5.length() > m_maxCurrent / 10)
        {
            drawLabel(t_painter, m_vector5Label, atan2(m_vector5.y(), m_vector5.x()), m_vector5Color, 0.5, m_labelPhiOffset);
        }

        drawVectorLine(t_painter, m_vector6, m_vector6Color, m_maxCurrent);
        drawArrowHead(t_painter, m_vector6, m_vector6Color, m_maxCurrent);
        if(m_vector6Label.isEmpty() == false && m_vector6.length() > m_maxCurrent / 10)
        {
            drawLabel(t_painter, m_vector6Label, atan2(m_vector6.y(), m_vector6.x()), m_vector6Color, 0.5, m_labelPhiOffset);
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


    if(m_vector1Label.isEmpty() == false && m_vector1.length() > m_maxVoltage / 10)
    {
        drawLabel(t_painter, m_vector1Label, atan2(m_vector1.y(), m_vector1.x()), m_vector1Color);
    }

    if(m_vector2Label.isEmpty() == false && m_vector2.length() > m_maxVoltage / 10)
    {
        drawLabel(t_painter, m_vector2Label, atan2(m_vector2.y(), m_vector2.x()), m_vector2Color);
    }

    if(m_vector3Label.isEmpty() == false && m_vector3.length() > m_maxVoltage / 10)
    {
        drawLabel(t_painter, m_vector3Label, atan2(m_vector3.y(), m_vector3.x()), m_vector3Color);
    }
}

void PhasorDiagram::drawGridAndCircle(QPainter *t_painter)
{
    t_painter->setPen(QPen(Qt::gray, 1));

    //grid
    if(m_gridVisible)
    {
        //x axis
        t_painter->drawLine(m_fromX - m_maxVoltage * m_gridScale, m_fromY, m_fromX + m_maxVoltage * m_gridScale, m_fromY);

        //y axis
        t_painter->drawLine(m_fromX, m_fromY - m_maxVoltage * m_gridScale, m_fromX, m_fromY + m_maxVoltage * m_gridScale);
    }

    //circle
    if(m_circleVisible)
    {
        t_painter->drawArc(m_fromX-(m_gridScale * m_circleValue), m_fromY-(m_gridScale * m_circleValue),2 * m_gridScale * m_circleValue,2 * m_gridScale * m_circleValue, 0, 5760);
    }
}




void PhasorDiagram::synchronize(QQuickItem *t_item)
{
    PhasorDiagram *realItem  = static_cast<PhasorDiagram *>(t_item);
    Q_ASSERT(realItem != nullptr);

    m_fromX = realItem->fromX();
    m_fromY = realItem->fromY();
    m_phiOrigin = realItem->phiOrigin();
    m_gridScale = realItem->gridScale();
    m_maxVoltage = realItem->maxVoltage();
    m_maxCurrent = realItem->maxCurrent();
    m_currentVisible = realItem->currentVisible();
    m_vectorView = realItem->vectorView();
    m_vectorMode = realItem->vectorMode();
    m_gridVisible = realItem->gridVisible();
    m_gridColor = realItem->gridColor();
    m_circleVisible = realItem->circleVisible();
    m_circleColor = realItem->circleColor();
    m_circleValue = realItem->circleValue();
    m_labelPhiOffset = realItem->labelPhiOffset();

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
    if(tmpData.length() > 1)
    {
        m_vector1 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
    tmpData = realItem->vector2Data();
    if(tmpData.length() > 1)
    {
        m_vector2 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
    tmpData = realItem->vector3Data();
    if(tmpData.length() > 1)
    {
        m_vector3 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
    tmpData = realItem->vector4Data();
    if(tmpData.length() > 1)
    {
        m_vector4 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
    tmpData = realItem->vector5Data();
    if(tmpData.length() > 1)
    {
        m_vector5 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
    tmpData = realItem->vector6Data();
    if(tmpData.length() > 1)
    {
        m_vector6 = QVector2D(tmpData.at(0), tmpData.at(1));
    }
}


PhasorDiagram::PhasorDiagram(QQuickItem *t_parent) : QQuickPaintedItem(t_parent)
{
    m_defaultFont.setPixelSize(20);
    m_vector1Data.append(10);
    m_vector1Data.append(20);
}


void PhasorDiagram::paint(QPainter *t_painter)
{
    synchronize((QQuickItem*)this);
    drawGridAndCircle(t_painter);

    switch(m_vectorView)
    {
    case PhasorDiagram::VectorView::VIEW_STAR:
    {
        drawVoltageArrows(t_painter);
        drawCurrentArrows(t_painter);
        break;
    }
    case PhasorDiagram::VectorView::VIEW_TRIANGLE:
    {
        drawTriangle(t_painter);
        drawCurrentArrows(t_painter);
        break;
    }
    case PhasorDiagram::VectorView::VIEW_THREE_PHASE:
    {
        drawVoltageArrows(t_painter, sqrt(3.0f)); //concatenated voltage
        drawCurrentArrows(t_painter);
        break;
    }
    }
}
