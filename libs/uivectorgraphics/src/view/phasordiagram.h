#ifndef PHASORDIAGRAM_H
#define PHASORDIAGRAM_H

#include "vectorpainter.h"
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

#define Q_VECTOR_PROPERTY(type, variable, getter, setter) \
private: \
    Q_PROPERTY(type getter READ getter WRITE setter NOTIFY getter##Changed) \
    Q_SIGNALS: \
    void getter##Changed(); \
    public: \
    type const& getter() const { return variable; } \
    public Q_SLOTS: \
    void setter(type const &v) { \
        m_vectorPainter.setter(v); \
        if(v == variable) \
            return; \
        variable = v; \
        emit getter##Changed(); \
        update(); \
    } \
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

public:
    Q_VECTOR_PROPERTY(float, m_fromX, fromX, setFromX)
    Q_VECTOR_PROPERTY(float, m_fromY, fromY, setFromY)
    Q_VECTOR_PROPERTY(float, m_phiOrigin, phiOrigin, setPhiOrigin)
    Q_VECTOR_PROPERTY(float, m_gridScale, gridScale, setGridScale)
    Q_VECTOR_PROPERTY(bool,  m_gridVisible, gridVisible, setGridVisible)
    Q_VECTOR_PROPERTY(QColor,m_gridColor, gridColor, setGridColor)
    Q_VECTOR_PROPERTY(float, m_circleValue, circleValue, setCircleValue)
    Q_VECTOR_PROPERTY(bool,  m_circleVisible, circleVisible, setCircleVisible)
    Q_VECTOR_PROPERTY(QColor, m_circleColor, circleColor, setCircleColor)
    Q_VECTOR_PROPERTY(float, m_maxVoltage, maxVoltage, setMaxVoltage)
    Q_VECTOR_PROPERTY(float, m_minVoltage, minVoltage, setMinVoltage)
    Q_VECTOR_PROPERTY(float, m_maxCurrent, maxCurrent, setMaxCurrent)
    Q_VECTOR_PROPERTY(float, m_minCurrent, minCurrent, setMinCurrent)
    Q_VECTOR_PROPERTY(float, m_maxValueVoltage, maxValueVoltage, setMaxValueVoltage)
    Q_VECTOR_PROPERTY(float, m_maxValueCurrent, maxValueCurrent, setMaxValueCurrent)

    QNANO_PROPERTY(VectorView, m_vectorView, vectorView, setVectorView)
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

    void drawVectors(QPainter *painter, bool drawVoltages, bool drawCurrents, float t_voltageFactor=1);
    void drawCurrentArrows(QPainter *painter);
    void drawTriangle(QPainter *t_painter);
    float detectCollision(int uPhase);
    void inDataToVector2d();

    VectorPainter m_vectorPainter;

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

};

#endif // PHASORDIAGRAM_H

