#ifndef VECTORPAINTCONTROLLER_H
#define VECTORPAINTCONTROLLER_H

#include "abstractvectorpainter.h"
#include "vectorsettings.h"
#include "vectorsettingsstatic.h"
#include <QColor>
#include <QVector>
#include <QVector2D>
#include <QSet>

class VectorPaintController : public AbstractVectorPainter
{
public:
    ~VectorPaintController() = default;

    enum class VectorType : int // this must be in sync to PhasorDiagram::VectorType - suggestions?
    {
        VIEW_STAR = 0,
        VIEW_TRIANGLE = 1,
        VIEW_THREE_PHASE = 2
    };

    void setVectorType(VectorType vectorType);
    VectorSettings* getVectorSettings();

    void setVectorLabel(int idx, const QString &vectorLabel);
    void setVectorColor(int idx, const QColor &vectorColor);

    void setVector(int idx, const QVector2D &vector);

    void paint(QPainter *painter) override;

private:
    // API
    VectorSettings m_vectorSettings;
    VectorType m_vectorType = VectorType::VIEW_STAR;

    QVector<QColor> m_vectorColor = QVector<QColor>(VectorSettingsStatic::COUNT_VECTORS);
    QVector<QString> m_vectorLabel = QVector<QString>(VectorSettingsStatic::COUNT_VECTORS);

    QVector<QVector2D> m_vector = QVector<QVector2D>(VectorSettingsStatic::COUNT_VECTORS);

};

#endif // VECTORPAINTCONTROLLER_H
