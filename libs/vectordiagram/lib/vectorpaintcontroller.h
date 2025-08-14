#ifndef VECTORPAINTCONTROLLER_H
#define VECTORPAINTCONTROLLER_H

#include "abstractvectorpainter.h"
#include "vectorsettings.h"
#include "vectorconstants.h"
#include "vectorgroupspainter.h"

class VectorPaintController : public AbstractVectorPainter
{
public:
    ~VectorPaintController() = default;

    VectorSettings* getVectorSettings();

    void setVectorLabel(int idx, const QString &vectorLabel);
    void setVectorColor(int idx, const QColor &vectorColor);

    void setVector(int idx, const QVector2D &vector);

    void paint(QPainter *painter) override;

private:
    void adjustAngleSettings(const VectorDataCurrent& currentVectors);
    void calcAndSetMaxValues(const VectorDataCurrent& currentVectors);

    VectorSettings m_vectorSettings;

    QVector<QColor> m_inVectorColors = QVector<QColor>(VectorConstants::COUNT_VECTORS);
    QVector<QString> m_inVectorLabels = QVector<QString>(VectorConstants::COUNT_VECTORS);
    QVector<QVector2D> m_inVectors = QVector<QVector2D>(VectorConstants::COUNT_VECTORS);
};

#endif // VECTORPAINTCONTROLLER_H
