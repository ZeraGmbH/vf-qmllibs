#ifndef VECTORPAINTER_H
#define VECTORPAINTER_H

#include <QColor>
#include <QVector>
#include <QPainter>
#include <QFont>
#include <QVector2D>
#include <QSet>

class VectorPainter
{
public:
    ~VectorPainter() = default;

    static constexpr int COUNT_PHASES = 3;
    enum class VectorView : int // this must be in sync to PhasorDiagram::VectorView - suggestions?
    {
        VIEW_STAR = 0,
        VIEW_TRIANGLE = 1,
        VIEW_THREE_PHASE = 2
    };

    void setPhiOrigin(const float &phiOrigin);
    void setGridScale(float gridScale);
    void setMaxVoltage(float maxVoltage);
    void setMinVoltage(float minVoltage);
    void setMaxCurrent(float maxCurrent);
    void setMinCurrent(float minCurrent);
    void setVectorView(VectorView vectorView);
    void setMaxValueVoltage(float maxValueVoltage);
    void setMaxValueCurrent(float maxValueCurrent);
    void setGridVisible(bool gridVisible);
    void setGridColor(const QColor& gridColor);
    void setCircleVisible(bool circleVisible);
    void setCircleColor(const QColor& circleColor);
    void setCircleValue(float circleValue);
    void setForceI1Top(bool forceI1Top);

    void setVector(int idx, const QVector2D &vector);
    void setVectorColor(int idx, const QColor &vectorColor);
    void setVectorLabel(int idx, const QString &vectorLabel);

    void paint(QPainter *painter);

private:
    void drawGridAndCircle(QPainter *painter);
    void drawVectors(QPainter *painter, bool drawVoltages, bool drawCurrents, float voltageFactor=1);
    void drawLabel(QPainter *painter,
                   int idx,
                   const QFont &font,
                   float scale=1,
                   float labelPhiOffset=0);
    void drawVectorLine(QPainter *painter, int idx, float maxValue);
    void drawArrowHead(QPainter *painter, int idx, float maxValue);
    void drawTriangle(QPainter *painter);
    void drawCenterPoint(QPainter *painter);

    static float pixelScale(QPainter *painter, float base);
    static int height(QPainter *painter);
    static int width(QPainter *painter);
    static float labelVectorLen(float screenLen);
    float detectCollision(int uPhase);

    // API
    float m_fromX = 0.0;
    float m_fromY = 0.0;
    float m_phiOrigin = 0.0;
    float m_gridScale = 0.0;
    float m_maxVoltage = 0.0;
    float m_minVoltage = 0.0;
    float m_maxCurrent = 0.0;
    float m_minCurrent = 0.0;
    VectorView m_vectorView = VectorView::VIEW_STAR;
    float m_maxValueVoltage = 0.0;
    float m_maxValueCurrent = 0.0;
    bool m_gridVisible = false;
    QColor m_gridColor = Qt::darkGray;
    bool m_circleVisible = false;
    QColor m_circleColor = Qt::darkGray;
    float m_circleValue = 0.0;
    bool m_forceI1Top = false;

    QVector<QVector2D> m_vector = QVector<QVector2D>(COUNT_PHASES*2);
    QVector<QColor> m_vectorColor = QVector<QColor>(COUNT_PHASES*2);
    QVector<QString> m_vectorLabel = QVector<QString>(COUNT_PHASES*2);

    // internal
    QFont m_defaultFont;
    QVector2D m_vectorUScreen[COUNT_PHASES];
    QSet<int> m_SetUCollisions; // key: I
    float m_currLabelRotateAngleU;
    float m_currLabelRotateAngleI;
};

#endif // VECTORPAINTER_H
