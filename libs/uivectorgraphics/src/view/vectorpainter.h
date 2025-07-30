#ifndef VECTORPAINTER_H
#define VECTORPAINTER_H

#include <QColor>
#include <QVector>
#include <QPainter>
#include <QVector2D>

class VectorPainter
{
public:
    ~VectorPainter() = default;
    static constexpr int COUNT_PHASES = 3;
    enum class VectorView : int
    {
        VIEW_STAR = 0,
        VIEW_TRIANGLE = 1,
        VIEW_THREE_PHASE = 2
    };
    void setFromX(const float &fromX);
    void setFromY(const float &fromY);
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

public: // during transition -> will turn private
    static float pixelScale(QPainter *painter, float base);
    void drawCenterPoint(QPainter *painter);
    void drawLabel(QPainter *painter,
                   int idx,
                   const QFont &font,
                   float scale=1,
                   float labelPhiOffset=0);
    void drawVectorLine(QPainter *painter, QVector2D vector, QColor color, float maxValue);
    void drawArrowHead(QPainter *painter, QVector2D vector, QColor color, float maxValue);
    void drawGridAndCircle(QPainter *painter);

    static float labelVectorLen(float screenLen);

private:
    void drawVectors(QPainter *painter, bool drawVoltages, bool drawCurrents, float voltageFactor=1);
    void drawCurrentArrows(QPainter *painter);
    void drawTriangle(QPainter *painter);
    float detectCollision(int uPhase);

    static int height(QPainter *painter);
    static int width(QPainter *painter);

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
};

#endif // VECTORPAINTER_H
