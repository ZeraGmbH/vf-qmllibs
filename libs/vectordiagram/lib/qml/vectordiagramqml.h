#ifndef VECTORDIAGRAMQML_H
#define VECTORDIAGRAMQML_H

#include "vectorpaintcontroller.h"
#include "vectordiagramqmlmacros.h"
#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QVector2D>
#include <QPainter>

// VectorDiagramQml is the QML property interface to VectorPaintController
class VectorDiagramQml: public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit VectorDiagramQml(QQuickItem *parent = nullptr);

    Q_ENUM(VectorType)

    // TODO vectorType
    //Q_VECTOR_PROPERTY(float, m_maxOvershootFactor, maxOvershootFactor, setMaxOvershootFactor)
    //Q_VECTOR_PROPERTY(float, m_nominalVoltage, nominalVoltage, setNominalVoltage)
    //Q_VECTOR_PROPERTY(float, m_minVoltage, minVoltage, setMinVoltage)
    //Q_VECTOR_PROPERTY(float, m_nominalCurrent, nominalCurrent, setNominalCurrent)
    //Q_VECTOR_PROPERTY(float, m_minCurrent, minCurrent, setMinCurrent)
    //Q_VECTOR_PROPERTY(bool,  m_coordCrossVisible, coordCrossVisible, setCoordCrossVisible)
    //Q_VECTOR_PROPERTY(QColor,m_coordCrossColor, coordCrossColor, setCoordCrossColor)
    //Q_VECTOR_PROPERTY(bool,  m_circleVisible, circleVisible, setCircleVisible)
    //Q_VECTOR_PROPERTY(QColor, m_circleColor, circleColor, setCircleColor)

    // create setVectorLabel0.. Q_PROPERTIES (getter / setter / notifier)
    Q_VECTOR_ARRAY_PROPERTY(QString, 0, m_vectorLabel, vectorLabel, setVectorLabel)
    Q_VECTOR_ARRAY_PROPERTY(QString, 1, m_vectorLabel, vectorLabel, setVectorLabel)
    Q_VECTOR_ARRAY_PROPERTY(QString, 2, m_vectorLabel, vectorLabel, setVectorLabel)
    Q_VECTOR_ARRAY_PROPERTY(QString, 3, m_vectorLabel, vectorLabel, setVectorLabel)
    Q_VECTOR_ARRAY_PROPERTY(QString, 4, m_vectorLabel, vectorLabel, setVectorLabel)
    Q_VECTOR_ARRAY_PROPERTY(QString, 5, m_vectorLabel, vectorLabel, setVectorLabel)

    // create vectorColor0.. Q_PROPERTIES (getter / setter / notifier)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 0, m_vectorColor, vectorColor, setVectorColor)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 1, m_vectorColor, vectorColor, setVectorColor)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 2, m_vectorColor, vectorColor, setVectorColor)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 3, m_vectorColor, vectorColor, setVectorColor)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 4, m_vectorColor, vectorColor, setVectorColor)
    Q_VECTOR_ARRAY_PROPERTY(QColor, 5, m_vectorColor, vectorColor, setVectorColor)

    // create vectorData0.. Q_PROPERTIES (getter / setter+conversion->QVector2D / notifier)
    Q_VECTOR_DATA_ARRAY_PROPERTY(0)
    Q_VECTOR_DATA_ARRAY_PROPERTY(1)
    Q_VECTOR_DATA_ARRAY_PROPERTY(2)
    Q_VECTOR_DATA_ARRAY_PROPERTY(3)
    Q_VECTOR_DATA_ARRAY_PROPERTY(4)
    Q_VECTOR_DATA_ARRAY_PROPERTY(5)

private:
    void paint(QPainter *painter) override;

    VectorPaintController m_vectorPainter;
};

#endif // VECTORDIAGRAMQML_H

