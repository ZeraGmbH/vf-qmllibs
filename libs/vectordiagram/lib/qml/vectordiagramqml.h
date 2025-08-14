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

    Q_ENUM(VectorStandard)
    Q_ENUM(VectorType)
    Q_ENUM(VectorNominals)

    // TODO maybe vectorWidthMode
    Q_VECTOR_PROPERTY(vectorStandard, VectorStandard, m_user, getVectorStandard, setVectorStandard)
    Q_VECTOR_PROPERTY(vectorType, VectorType, m_user, getVectorType, setVectorType)
    Q_VECTOR_PROPERTY(nominalSelection, VectorNominals, m_lengths, getNominalSelection, setNominalSelection)
    Q_VECTOR_PROPERTY(maxOvershootFactor, float, m_lengths, getMaxOvershootFactor, setMaxOvershootFactor)
    Q_VECTOR_PROPERTY(nominalVoltage, float, m_lengths, getNomVoltage, setNomVoltage)
    Q_VECTOR_PROPERTY(minVoltage, float, m_lengths, getMinVoltage, setMinVoltage)
    Q_VECTOR_PROPERTY(nominalCurrent, float, m_lengths, getNomCurrent, setNomCurrent)
    Q_VECTOR_PROPERTY(minCurrent, float, m_lengths, getMinCurrent, setMinCurrent)
    Q_VECTOR_PROPERTY(coordCrossColor, QColor, m_layout, getCoordCrossColor, setCoordCrossColor)
    Q_VECTOR_PROPERTY(circleColor, QColor, m_layout, getCircleColor, setCircleColor)

    Q_PROPERTY(float maxVoltage READ maxVoltage NOTIFY maxVoltageChanged)
    Q_SIGNAL void maxVoltageChanged();
    float maxVoltage();
    Q_PROPERTY(float maxCurrent READ maxCurrent NOTIFY maxCurrentChanged)
    Q_SIGNAL void maxCurrentChanged();
    float maxCurrent();

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
