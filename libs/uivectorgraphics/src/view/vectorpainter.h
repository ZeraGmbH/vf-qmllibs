#ifndef VECTORPAINTER_H
#define VECTORPAINTER_H

#include <QColor>
#include <QList>
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
    void setDisplayStyle(VectorView displayStyle);
    void setMaxValueVoltage(float maxValueVoltage);
    void setMaxValueCurrent(float maxValueCurrent);
    void setGridVisible(bool gridVisible);
    void setGridColor(const QColor& gridColor);
    void setCircleVisible(bool circleVisible);
    void setCircleColor(const QColor& circleColor);
    void setCircleValue(float circleValue);
    void setForceI1Top(bool forceI1Top);

    void setVector1Data(const QList<double> &vector1Data);
    void setVector2Data(const QList<double> &vector2Data);
    void setVector3Data(const QList<double> &vector3Data);
    void setVector4Data(const QList<double> &vector4Data);
    void setVector5Data(const QList<double> &vector5Data);
    void setVector6Data(const QList<double> &vector6Data);

    void setVector1Color(const QColor &vector1Color);
    void setVector2Color(const QColor &vector2Color);
    void setVector3Color(const QColor &vector3Color);
    void setVector4Color(const QColor &vector4Color);
    void setVector5Color(const QColor &vector5Color);
    void setVector6Color(const QColor &vector6Color);

    void setVector1Label(const QString &vector1Label);
    void setVector2Label(const QString &vector2Label);
    void setVector3Label(const QString &vector3Label);
    void setVector4Label(const QString &vector4Label);
    void setVector5Label(const QString &vector5Label);
    void setVector6Label(const QString &vector6Label);

    void paint(QPainter *painter);

public: // during transition -> will turn private
    static float pixelScale(QPainter *painter, float base);
    void drawCenterPoint(QPainter *painter);
    void drawLabel(QPainter *painter, const QString &label, const QFont &font, float vectorPhi, QColor color, float scale=1, float labelPhiOffset=0);
    void drawVectorLine(QPainter *painter, QVector2D vector, QColor color, float maxValue);
    void drawArrowHead(QPainter *painter, QVector2D vector, QColor color, float maxValue);

private:
    void drawVectors(QPainter *painter, bool drawVoltages, bool drawCurrents, float voltageFactor=1);
    void drawCurrentArrows(QPainter *painter);
    void drawTriangle(QPainter *painter);
    void drawGridAndCircle(QPainter *painter);
    float labelVectorLen(float screenLen);
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
    VectorView m_displayStyle = VectorView::VIEW_STAR;
    float m_maxValueVoltage = 0.0;
    float m_maxValueCurrent = 0.0;
    bool m_gridVisible = false;
    QColor m_gridColor;
    bool m_circleVisible = false;
    QColor m_circleColor;
    float m_circleValue = 0.0;
    bool m_forceI1Top = false;

    const QList<double> m_vector1Data;
    const QList<double> m_vector2Data;
    const QList<double> m_vector3Data;
    const QList<double> m_vector4Data;
    const QList<double> m_vector5Data;
    const QList<double> m_vector6Data;

    QColor m_vector1Color;
    QColor m_vector2Color;
    QColor m_vector3Color;
    QColor m_vector4Color;
    QColor m_vector5Color;
    QColor m_vector6Color;

    QString m_vector1Label;
    QString m_vector2Label;
    QString m_vector3Label;
    QString m_vector4Label;
    QString m_vector5Label;
    QString m_vector6Label;
};

#endif // VECTORPAINTER_H
