#ifndef PHASORDIAGRAM_H
#define PHASORDIAGRAM_H

#include <QQuickPaintedItem>
#include <QQuickItem>


#include <QVector2D>
#include <QPainter>

#define QNANO_PROPERTY(type, variable, getter, setter) \
    private: \
    Q_PROPERTY(type getter READ getter WRITE setter NOTIFY getter##Changed) \
    Q_SIGNALS: \
    void getter##Changed(); \
    public: \
    type const& getter() const { return variable; } \
    public Q_SLOTS: \
    void setter(type const &v) { if(v == variable) return; variable = v; emit getter##Changed(); update(); } \
    private: \
    type variable;


/**
 * @brief Paints the phasor diagram (VectorModulePage.qml)
 */
class PhasorDiagram: public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit PhasorDiagram(QQuickItem *t_parent = nullptr);

    enum class VectorView : int
    {
        VIEW_STAR = 0,
        VIEW_TRIANGLE = 1,
        VIEW_THREE_PHASE = 2
    };
    Q_ENUM(VectorView)

    QNANO_PROPERTY(float, m_fromX, fromX, setFromX)
    QNANO_PROPERTY(float, m_fromY, fromY, setFromY)
    QNANO_PROPERTY(float, m_phiOrigin, phiOrigin, setPhiOrigin)
    QNANO_PROPERTY(float, m_gridScale, gridScale, setGridScale)
    QNANO_PROPERTY(float, m_maxVoltage, maxVoltage, setMaxVoltage)
    QNANO_PROPERTY(float, m_minVoltage, minVoltage, setMinVoltage)
    QNANO_PROPERTY(float, m_maxCurrent, maxCurrent, setMaxCurrent)
    QNANO_PROPERTY(float, m_minCurrent, minCurrent, setMinCurrent)
    QNANO_PROPERTY(VectorView, m_vectorView, vectorView, setVectorView)
    QNANO_PROPERTY(float, m_maxValueVoltage, maxValueVoltage, setMaxValueVoltage)
    QNANO_PROPERTY(float, m_maxValueCurrent, maxValueCurrent, setMaxValueCurrent)
    QNANO_PROPERTY(bool, m_gridVisible, gridVisible, setGridVisible)
    QNANO_PROPERTY(QColor, m_gridColor, gridColor, setGridColor)
    QNANO_PROPERTY(bool, m_circleVisible, circleVisible, setCircleVisible)
    QNANO_PROPERTY(QColor, m_circleColor, circleColor, setCircleColor)
    QNANO_PROPERTY(float, m_circleValue, circleValue, setCircleValue)
    QNANO_PROPERTY(bool, m_forceI1Top, forceI1Top, setForceI1Top)

    QNANO_PROPERTY(QList<double>, m_vector1Data, vector1Data, setVector1Data)
    QNANO_PROPERTY(QList<double>, m_vector2Data, vector2Data, setVector2Data)
    QNANO_PROPERTY(QList<double>, m_vector3Data, vector3Data, setVector3Data)
    QNANO_PROPERTY(QList<double>, m_vector4Data, vector4Data, setVector4Data)
    QNANO_PROPERTY(QList<double>, m_vector5Data, vector5Data, setVector5Data)
    QNANO_PROPERTY(QList<double>, m_vector6Data, vector6Data, setVector6Data)

    QNANO_PROPERTY(QColor, m_vector1Color, vector1Color, setVector1Color)
    QNANO_PROPERTY(QColor, m_vector2Color, vector2Color, setVector2Color)
    QNANO_PROPERTY(QColor, m_vector3Color, vector3Color, setVector3Color)
    QNANO_PROPERTY(QColor, m_vector4Color, vector4Color, setVector4Color)
    QNANO_PROPERTY(QColor, m_vector5Color, vector5Color, setVector5Color)
    QNANO_PROPERTY(QColor, m_vector6Color, vector6Color, setVector6Color)

    QNANO_PROPERTY(QString, m_vector1Label, vector1Label, setVector1Label)
    QNANO_PROPERTY(QString, m_vector2Label, vector2Label, setVector2Label)
    QNANO_PROPERTY(QString, m_vector3Label, vector3Label, setVector3Label)
    QNANO_PROPERTY(QString, m_vector4Label, vector4Label, setVector4Label)
    QNANO_PROPERTY(QString, m_vector5Label, vector5Label, setVector5Label)
    QNANO_PROPERTY(QString, m_vector6Label, vector6Label, setVector6Label)

private:
    // Reimplement
    void paint(QPainter *t_painter) override;

    float pixelScale(float t_base);
    void drawLabel(QPainter *t_painter, const QString &t_label, float t_vectorPhi, QColor t_color, float t_scale=1, float t_labelPhiOffset=0);
    void drawArrowHead(QPainter *t_painter, QVector2D t_vector, QColor t_color, float t_maxValue);
    void drawVectorLine(QPainter *t_painter, QVector2D t_vector, QColor t_color, float t_maxValue);
    void drawVectors(QPainter *t_painter, bool drawVoltages, bool drawCurrents, float t_voltageFactor=1);
    void drawCurrentArrows(QPainter *t_painter);
    void drawTriangle(QPainter *t_painter);
    void drawGridAndCircle(QPainter *t_painter);
    void drawCenterPoint(QPainter *t_painter);
    float labelVectorLen(float screenLen);
    float detectCollision(int uPhase);

    static constexpr int COUNT_PHASES = 3;
    QVector2D m_vector1;
    QVector2D m_vector2;
    QVector2D m_vector3;
    QVector2D m_vector4;
    QVector2D m_vector5;
    QVector2D m_vector6;
    QVector2D m_vectorUScreen[COUNT_PHASES];
    QSet<int> m_SetUCollisions; // key: I
    QFont m_defaultFont;
    float m_currLabelRotateAngleU;
    float m_currLabelRotateAngleI;

protected:
    void synchronize(QQuickItem *t_item);
};

#endif // PHASORDIAGRAM_H

