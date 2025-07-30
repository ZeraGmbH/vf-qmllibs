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
    explicit PhasorDiagram(QQuickItem *parent = nullptr);

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

#define Q_VECTOR_ARRAY_PROPERTY(type, idx, variable, getter, setter) \
private: \
    Q_PROPERTY(type getter##idx READ getter##idx WRITE setter##idx NOTIFY getter##Changed##idx) \
Q_SIGNALS: \
    void getter##Changed##idx(); \
public: \
    type const& getter##idx() const { return variable##idx; } \
public Q_SLOTS: \
    void setter##idx(type const &v) { \
        m_vectorPainter.setter(idx, v); \
        if(v == variable##idx) \
            return; \
        variable##idx = v; \
        emit getter##Changed##idx(); \
        update(); \
    } \
private: \
    type variable##idx;
// end Q_VECTOR_ARRAY_PROPERTY

    // create vectorColor0.. Q_PROPERTIES (getter / setter / notifier)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 0, m_vectorColor, vectorColor, setVectorColor)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 1, m_vectorColor, vectorColor, setVectorColor)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 2, m_vectorColor, vectorColor, setVectorColor)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 3, m_vectorColor, vectorColor, setVectorColor)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 4, m_vectorColor, vectorColor, setVectorColor)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 5, m_vectorColor, vectorColor, setVectorColor)

    // create setVectorLabel0.. Q_PROPERTIES (getter / setter / notifier)
    Q_VECTOR_ARRAY_PROPERTY(QString, 0, m_vectorLabel, vectorLabel, setVectorLabel)
    Q_VECTOR_ARRAY_PROPERTY(QString, 1, m_vectorLabel, vectorLabel, setVectorLabel)
    Q_VECTOR_ARRAY_PROPERTY(QString, 2, m_vectorLabel, vectorLabel, setVectorLabel)
    Q_VECTOR_ARRAY_PROPERTY(QString, 3, m_vectorLabel, vectorLabel, setVectorLabel)
    Q_VECTOR_ARRAY_PROPERTY(QString, 4, m_vectorLabel, vectorLabel, setVectorLabel)
    Q_VECTOR_ARRAY_PROPERTY(QString, 5, m_vectorLabel, vectorLabel, setVectorLabel)

#define Q_VECTOR_DATA_ARRAY_PROPERTY(idx) \
private: \
        Q_PROPERTY(QList<double> vectorData##idx READ vectorData##idx WRITE setVectorData##idx NOTIFY vectorDataChanged##idx) \
        Q_SIGNALS: \
        void vectorDataChanged##idx(); \
    public: \
    const QList<double> &vectorData##idx() const { return m_vectorData##idx; } \
        public Q_SLOTS: \
        void setVectorData##idx(const QList<double> &v) \
    { \
            if (v.length() > 1) \
            m_vectorPainter.setVector(idx, QVector2D(v.at(0), v.at(1))); \
            if(v == m_vectorData##idx) \
            return; \
            m_vectorData##idx = v; \
            emit vectorDataChanged##idx(); \
            update(); \
    } \
    private: \
    QList<double> m_vectorData##idx;
    // end Q_VECTOR_DATA_ARRAY_PROPERTY

    // create vectorData0.. Q_PROPERTIES (getter / setter+conversion->QVector2D / notifier)
    Q_VECTOR_DATA_ARRAY_PROPERTY(0)
    Q_VECTOR_DATA_ARRAY_PROPERTY(1)
    Q_VECTOR_DATA_ARRAY_PROPERTY(2)
    Q_VECTOR_DATA_ARRAY_PROPERTY(3)
    Q_VECTOR_DATA_ARRAY_PROPERTY(4)
    Q_VECTOR_DATA_ARRAY_PROPERTY(5)

private:
    // Reimplement
    void paint(QPainter *painter) override;

    void drawVectors(QPainter *painter, bool drawVoltages, bool drawCurrents, float voltageFactor=1);
    void drawCurrentArrows(QPainter *painter);
    void drawTriangle(QPainter *painter);
    void inDataToVector2d();

    VectorPainter m_vectorPainter;

    static constexpr int COUNT_PHASES = 3;
    QVector2D m_vector0;
    QVector2D m_vector1;
    QVector2D m_vector2;
    QVector2D m_vector3;
    QVector2D m_vector4;
    QVector2D m_vector5;
    QFont m_defaultFont;
    float m_currLabelRotateAngleU;
    float m_currLabelRotateAngleI;

};

#endif // PHASORDIAGRAM_H

