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
        m_vectorPainter.drawTriangle(painter);
        m_vectorPainter.drawVectors(painter, false, true);
        break;
    case PhasorDiagram::VectorView::VIEW_THREE_PHASE:
        m_vectorPainter.m_currLabelRotateAngleU = LABEL_ROTATE_ANGLE_3PH_U;
        m_vectorPainter.m_currLabelRotateAngleI = LABEL_ROTATE_ANGLE_3PH_I;
        m_vectorPainter.drawVectors(painter, true, true, sqrt(3.0f)/*concatenated voltage */);
        break;
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
