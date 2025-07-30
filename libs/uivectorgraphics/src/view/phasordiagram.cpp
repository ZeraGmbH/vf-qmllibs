#include "phasordiagram.h"
#include <QGradient>
#include <QPainterPath>
#include <math.h>

static constexpr float LABEL_ROTATE_ANGLE =  -6.0 * M_PI / 180;
// 3ph display has longer texts (e.g 'UL1-UL2') so needs to rotate more
static constexpr float LABEL_ROTATE_ANGLE_3PH_U =  -30.0 * M_PI/180;
static constexpr float LABEL_ROTATE_ANGLE_3PH_I =  -5.0 * M_PI/180;

PhasorDiagram::PhasorDiagram(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    m_gridColor(Qt::darkGray)
{
    setAntialiasing(true);
    setOpaquePainting(true);
}

void PhasorDiagram::paint(QPainter *painter)
{
    m_vectorPainter.paint(painter);
    inDataToVector2d();

    switch(m_vectorView)
    {
    case PhasorDiagram::VectorView::VIEW_STAR:
        m_vectorPainter.m_currLabelRotateAngleU = LABEL_ROTATE_ANGLE;
        m_vectorPainter.m_currLabelRotateAngleI = LABEL_ROTATE_ANGLE;
        m_vectorPainter.drawVectors(painter, true, true);
        break;
    case PhasorDiagram::VectorView::VIEW_TRIANGLE:
        m_vectorPainter.m_currLabelRotateAngleU = LABEL_ROTATE_ANGLE;
        m_vectorPainter.m_currLabelRotateAngleI = LABEL_ROTATE_ANGLE;
        drawTriangle(painter);
        m_vectorPainter.drawVectors(painter, false, true);
        break;
    case PhasorDiagram::VectorView::VIEW_THREE_PHASE:
        m_vectorPainter.m_currLabelRotateAngleU = LABEL_ROTATE_ANGLE_3PH_U;
        m_vectorPainter.m_currLabelRotateAngleI = LABEL_ROTATE_ANGLE_3PH_I;
        m_vectorPainter.drawVectors(painter, true, true, sqrt(3.0f)/*concatenated voltage */);
        break;
    }
}

void PhasorDiagram::drawTriangle(QPainter *painter)
{
    //Scale vectors and convert to x/y
    //v1
    const float v1Phi = atan2(m_vector0.y(), m_vector0.x()) - m_phiOrigin;
    const float v1X = m_fromX + m_gridScale * m_vector0.length() * cos(v1Phi);
    const float v1Y = m_fromY + m_gridScale * m_vector0.length() * sin(v1Phi);

    //v2
    const float v2Phi = atan2(m_vector1.y(), m_vector1.x()) - m_phiOrigin;
    const float v2X = m_fromX + m_gridScale * m_vector1.length() * cos(v2Phi);
    const float v2Y = m_fromY + m_gridScale * m_vector1.length() * sin(v2Phi);

    //v3
    const float v3Phi = atan2(m_vector2.y(), m_vector2.x()) - m_phiOrigin;
    const float v3X = m_fromX + m_gridScale * m_vector2.length() * cos(v3Phi);
    const float v3Y = m_fromY + m_gridScale * m_vector2.length() * sin(v3Phi);

    //Gradients
    //v1->v2
    QLinearGradient grd1(QPoint(v1X, v1Y), QPoint(v2X, v2Y));
    grd1.setColorAt(0,m_vectorColor0);
    grd1.setColorAt(1,m_vectorColor1);

    //v2->v3
    QLinearGradient grd2(QPoint(v2X, v2Y), QPoint(v3X, v3Y));
    grd2.setColorAt(0,m_vectorColor1);
    grd2.setColorAt(1,m_vectorColor2);

    //v3->v1
    QLinearGradient grd3(QPoint(v3X, v3Y), QPoint(v1X, v1Y));
    grd3.setColorAt(0,m_vectorColor2);
    grd3.setColorAt(1,m_vectorColor0);

    //--Draw--//////////////////////// v1 -> v2
    painter->setPen(QPen(grd1, 2));
    painter->drawLine(v1X, v1Y,v2X, v2Y);

    //--Draw--//////////////////////// v2 -> v3
    painter->setPen(QPen(grd2, 2));
    painter->drawLine(v2X, v2Y,v3X, v3Y);

    //--Draw--//////////////////////// v3 -> v1
    painter->setPen(QPen(grd3, 2));
    painter->drawLine(v3X, v3Y,v1X, v1Y);

    if(m_vectorLabel0.isEmpty() == false && m_vector0.length() > m_maxVoltage / 10) {
        m_vectorPainter.m_vectorUScreen[0] = m_vector0 / m_maxVoltage;
        float screenLenLabel = m_vectorPainter.m_vectorUScreen[0].length();
         m_vectorPainter.drawLabel(
            painter,
            0,
            m_vectorPainter.m_defaultFont,
            m_vectorPainter.labelVectorLen(screenLenLabel),
                  (1/screenLenLabel)*m_vectorPainter.m_currLabelRotateAngleU*m_vectorPainter.detectCollision(0));
    }

    if(m_vectorLabel1.isEmpty() == false && m_vector1.length() > m_maxVoltage / 10) {
        m_vectorPainter.m_vectorUScreen[1] = m_vector1 / m_maxVoltage;
        float screenLenLabel = m_vectorPainter.m_vectorUScreen[1].length();
         m_vectorPainter.drawLabel(
            painter,
            1,
            m_vectorPainter.m_defaultFont,
            m_vectorPainter.labelVectorLen(screenLenLabel),
            (1/screenLenLabel)*m_vectorPainter.m_currLabelRotateAngleU*m_vectorPainter.detectCollision(1));
    }

    if(m_vectorLabel2.isEmpty() == false && m_vector2.length() > m_maxVoltage / 10) {
        m_vectorPainter.m_vectorUScreen[2] = m_vector2 / m_maxVoltage;
        float screenLenLabel = m_vectorPainter.m_vectorUScreen[2].length();
         m_vectorPainter.drawLabel(
            painter,
            2,
            m_vectorPainter.m_defaultFont,
            m_vectorPainter.labelVectorLen(screenLenLabel),
            (1/screenLenLabel)*m_vectorPainter.m_currLabelRotateAngleU*m_vectorPainter.detectCollision(2));
    }
}

void PhasorDiagram::inDataToVector2d()
{
    if (vectorData0().length() > 1)
        m_vector0 = QVector2D(vectorData0().at(0), vectorData0().at(1));
    if (vectorData1().length() > 1)
        m_vector1 = QVector2D(vectorData1().at(0), vectorData1().at(1));
    if (vectorData2().length() > 1)
        m_vector2 = QVector2D(vectorData2().at(0), vectorData2().at(1));
    if (vectorData3().length() > 1)
        m_vector3 = QVector2D(vectorData3().at(0), vectorData3().at(1));
    if (vectorData4().length() > 1)
        m_vector4 = QVector2D(vectorData4().at(0), vectorData4().at(1));
    if (vectorData5().length() > 1)
        m_vector5 = QVector2D(vectorData5().at(0), vectorData5().at(1));
}
