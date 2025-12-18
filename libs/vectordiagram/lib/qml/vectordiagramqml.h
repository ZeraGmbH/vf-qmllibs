#ifndef VECTORDIAGRAMQML_H
#define VECTORDIAGRAMQML_H

#include "vectorpaintcontroller.h"
#include "vectordiagramqmlmacros.h"
#include "pseudocrcbuffer.h"
#include <timertemplateqt.h>
#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QVector2D>
#include <QPainter>
#include <QByteArray>

// VectorDiagramQml is the QML property interface to VectorPaintController
class VectorDiagramQml: public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit VectorDiagramQml(QQuickItem *parent = nullptr);

    // DIN / ISO / ANSI
    Q_VECTOR_PROPERTY(vectorStandard, VectorSettingsUser::VectorStandard, m_user, getVectorStandard, setVectorStandard)
    // star / Δ / 3wire
    Q_VECTOR_PROPERTY(vectorType, VectorSettingsUser::VectorType, m_user, getVectorType, setVectorType)
    // ZENUX: oldschool / WEBSAM: WebSam alike style (currents wider)
    Q_VECTOR_PROPERTY(vectorStyle, VectorSettingsLayout::VectorStyle, m_layout, getVectorStyle, setVectorStyle)

    // NOMINAL: Vectors with nominal length end on circle / MAXIMUM: Vectors with max length end on circle
    Q_VECTOR_PROPERTY(nominalSelection, VectorSettingsLengths::VectorNominals, m_lengths, getNominalSelection, setNominalSelection)
    // effective for nominalSelection == VectorNominals::NOMINAL
    Q_VECTOR_PROPERTY(nominalVoltage, float, m_lengths, getNomVoltage, setNomVoltage)
    // effective for nominalSelection == VectorNominals::NOMINAL
    Q_VECTOR_PROPERTY(nominalCurrent, float, m_lengths, getNomCurrent, setNomCurrent)

    // vectors shorter than min are not drawn
    Q_VECTOR_PROPERTY(minVoltage, float, m_lengths, getMinVoltage, setMinVoltage)
    Q_VECTOR_PROPERTY(minCurrent, float, m_lengths, getMinCurrent, setMinCurrent)

    Q_VECTOR_PROPERTY(maxOvershootFactor, float, m_lengths, getMaxOvershootFactor, setMaxOvershootFactor)
    Q_VECTOR_PROPERTY(coordCrossColor, QColor, m_layout, getCoordCrossColor, setCoordCrossColor)
    Q_VECTOR_PROPERTY(circleColor, QColor, m_layout, getCircleColor, setCircleColor)

    // Readonly helpers for vector view radius values
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

private slots:
    void onUpdateTimer();
private:
    void paint(QPainter *painter) override;
    void startUpdate();

    VectorPaintController m_vectorPainter;
    TimerTemplateQtPtr m_updateTimer;
    quint32 m_lastPaintCrc = PseudoCrcBuffer::InitialCrc;
};

#endif // VECTORDIAGRAMQML_H
