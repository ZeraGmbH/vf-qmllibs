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
// end Q_VECTOR_PROPERTY

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

    QNANO_PROPERTY(QList<double>, m_vectorData0, vectorData0, setVectorData0)
    QNANO_PROPERTY(QList<double>, m_vectorData1, vectorData1, setVectorData1)
    QNANO_PROPERTY(QList<double>, m_vectorData2, vectorData2, setVectorData2)
    QNANO_PROPERTY(QList<double>, m_vectorData3, vectorData3, setVectorData3)
    QNANO_PROPERTY(QList<double>, m_vectorData4, vectorData4, setVectorData4)
    QNANO_PROPERTY(QList<double>, m_vectorData5, vectorData5, setVectorData5)

#define Q_VECTOR_ARRAY_PROPERTY(type, variable, getter, setter) \
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
    // end Q_VECTOR_ARRAY_PROPERTY
    QNANO_PROPERTY(QColor, m_vectorColor0, vectorColor0, setVectorColor0)
    QNANO_PROPERTY(QColor, m_vectorColor1, vectorColor1, setVectorColor1)
    QNANO_PROPERTY(QColor, m_vectorColor2, vectorColor2, setVectorColor2)
    QNANO_PROPERTY(QColor, m_vectorColor3, vectorColor3, setVectorColor3)
    QNANO_PROPERTY(QColor, m_vectorColor4, vectorColor4, setVectorColor4)
    QNANO_PROPERTY(QColor, m_vectorColor5, vectorColor5, setVectorColor5)

    QNANO_PROPERTY(QString, m_vectorLabel0, vectorLabel0, setVectorLabel0)
    QNANO_PROPERTY(QString, m_vectorLabel1, vectorLabel1, setVectorLabel1)
    QNANO_PROPERTY(QString, m_vectorLabel2, vectorLabel2, setVectorLabel2)
    QNANO_PROPERTY(QString, m_vectorLabel3, vectorLabel3, setVectorLabel3)
    QNANO_PROPERTY(QString, m_vectorLabel4, vectorLabel4, setVectorLabel4)
    QNANO_PROPERTY(QString, m_vectorLabel5, vectorLabel5, setVectorLabel5)

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
    QVector2D m_vector0;
    QVector2D m_vector1;
    QVector2D m_vector2;
    QVector2D m_vector3;
    QVector2D m_vector4;
    QVector2D m_vector5;
    QVector2D m_vectorUScreen[COUNT_PHASES];
    QSet<int> m_SetUCollisions; // key: I
    QFont m_defaultFont;
    float m_currLabelRotateAngleU;
    float m_currLabelRotateAngleI;

};

#endif // PHASORDIAGRAM_H

