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
