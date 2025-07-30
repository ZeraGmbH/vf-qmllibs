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
    inDataToVector2d();
    m_defaultFont.setPixelSize(height() > 0.0 ? height() / 25 : 10.0);
    m_vectorPainter.drawGridAndCircle(painter);
    m_SetUCollisions.clear();

    switch(m_vectorView)
    {
    case PhasorDiagram::VectorView::VIEW_STAR:
        m_currLabelRotateAngleU = LABEL_ROTATE_ANGLE;
        m_currLabelRotateAngleI = LABEL_ROTATE_ANGLE;
        drawVectors(painter, true, true);
        break;
    case PhasorDiagram::VectorView::VIEW_TRIANGLE:
        m_currLabelRotateAngleU = LABEL_ROTATE_ANGLE;
        m_currLabelRotateAngleI = LABEL_ROTATE_ANGLE;
        drawTriangle(painter);
        drawVectors(painter, false, true);
        break;
    case PhasorDiagram::VectorView::VIEW_THREE_PHASE:
        m_currLabelRotateAngleU = LABEL_ROTATE_ANGLE_3PH_U;
        m_currLabelRotateAngleI = LABEL_ROTATE_ANGLE_3PH_I;
        drawVectors(painter, true, true, sqrt(3.0f)/*concatenated voltage */);
        break;
    }
}

void PhasorDiagram::drawVectors(QPainter *painter, bool drawVoltages, bool drawCurrents, float voltageFactor)
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
        QVector2D vectors[] = { m_vector0, m_vector1, m_vector2 };
        for(int idx = 0; idx < COUNT_PHASES; ++idx) {
            QVector2D vector = vectors[idx];
            m_vectorUScreen[idx] = vector / (m_maxVoltage * voltageFactor);
            if(vector.length() > m_minVoltage * voltageFactor) {
                float screenLenVector = m_vectorUScreen[idx].length();
                TVectorData currVectorData(idx,
                                           m_maxVoltage,
                                           voltageFactor,
                                           m_vectorPainter.labelVectorLen(screenLenVector),
                                           (1/screenLenVector)*m_currLabelRotateAngleU*detectCollision(idx));
                // negative len for long -> short order
                sortedVectors.insert(-screenLenVector, currVectorData);
            }
        }
    }
    // add currents sorted
    if(drawCurrents) {
        QVector2D vectors[] = { m_vector3, m_vector4, m_vector5 };
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
                                           m_vectorPainter.labelVectorLen(screenLenVectorI),
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
        m_vectorPainter.drawArrowHead(painter, vData.idx, vData.maxVal * vData.factorVal);
        m_vectorPainter.drawVectorLine(painter, vData.idx, vData.maxVal * vData.factorVal);
        m_vectorPainter.drawLabel(painter,
                                  vData.idx,
                                  m_defaultFont,
                                  vData.labelPositionScale,
                                  vData.labelPhiOffset);
    }

    // do not leave center on random colour
    if(sortedVectors.count() >1)
        m_vectorPainter.drawCenterPoint(painter);
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
        m_vectorUScreen[0] = m_vector0 / m_maxVoltage;
        float screenLenLabel = m_vectorUScreen[0].length();
         m_vectorPainter.drawLabel(
            painter,
            0,
            m_defaultFont,
            m_vectorPainter.labelVectorLen(screenLenLabel),
                  (1/screenLenLabel)*m_currLabelRotateAngleU*detectCollision(0));
    }

    if(m_vectorLabel1.isEmpty() == false && m_vector1.length() > m_maxVoltage / 10) {
        m_vectorUScreen[1] = m_vector1 / m_maxVoltage;
        float screenLenLabel = m_vectorUScreen[1].length();
         m_vectorPainter.drawLabel(
            painter,
            1,
            m_defaultFont,
            m_vectorPainter.labelVectorLen(screenLenLabel),
            (1/screenLenLabel)*m_currLabelRotateAngleU*detectCollision(1));
    }

    if(m_vectorLabel2.isEmpty() == false && m_vector2.length() > m_maxVoltage / 10) {
        m_vectorUScreen[2] = m_vector2 / m_maxVoltage;
        float screenLenLabel = m_vectorUScreen[2].length();
         m_vectorPainter.drawLabel(
            painter,
            2,
            m_defaultFont,
            m_vectorPainter.labelVectorLen(screenLenLabel),
            (1/screenLenLabel)*m_currLabelRotateAngleU*detectCollision(2));
    }
}

float PhasorDiagram::detectCollision(int uPhase)
{
    // check collision with I vectors
    QVector2D vectors[] = { m_vector3, m_vector4, m_vector5 };
    QString labels[] = { m_vectorLabel3, m_vectorLabel4, m_vectorLabel5 };

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
