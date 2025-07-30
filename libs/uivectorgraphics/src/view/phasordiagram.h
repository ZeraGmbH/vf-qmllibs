#ifndef PHASORDIAGRAM_H
#define PHASORDIAGRAM_H

#include "vectorpainter.h"
#include "phasordiagrampropertygeneratormacros.h"
#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QVector2D>
#include <QPainter>

// PhasorDiagram is the QML property interface to VectorPainter
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

    // create various Q_PROPERTIES (getter / setter / notifier)
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
    Q_VECTOR_PROPERTY(bool, m_forceI1Top, forceI1Top, setForceI1Top)

    Q_PROPERTY(VectorView vectorView READ vectorView WRITE setVectorView NOTIFY vectorViewChanged)
    const VectorView &vectorView();
    void setVectorView(const VectorView &vectorView);
    Q_SIGNAL void vectorViewChanged();

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

    // create vectorData0.. Q_PROPERTIES (getter / setter+conversion->QVector2D / notifier)
    Q_VECTOR_DATA_ARRAY_PROPERTY(0)
    Q_VECTOR_DATA_ARRAY_PROPERTY(1)
    Q_VECTOR_DATA_ARRAY_PROPERTY(2)
    Q_VECTOR_DATA_ARRAY_PROPERTY(3)
    Q_VECTOR_DATA_ARRAY_PROPERTY(4)
    Q_VECTOR_DATA_ARRAY_PROPERTY(5)

private:
    void paint(QPainter *painter) override;

    VectorPainter m_vectorPainter;
    VectorView m_vectorView;
};

#endif // PHASORDIAGRAM_H

