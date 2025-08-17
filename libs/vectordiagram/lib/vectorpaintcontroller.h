#ifndef VECTORPAINTCONTROLLER_H
#define VECTORPAINTCONTROLLER_H

#include "abstractvectorpainter.h"
#include "vectorsettings.h"
#include "vectorconstants.h"
#include "vectorgroupspainter.h"
#include <memory>

class VectorPaintController : public AbstractVectorPainter
{
public:
    VectorPaintController();
    ~VectorPaintController() = default;

    std::shared_ptr<VectorSettings> getVectorSettings() const;

    void setVectorLabel(int idx, const QString &vectorLabel);
    void setVectorColor(int idx, const QColor &vectorColor);

    void setVector(int idx, const QVector2D &vector);

    void paint(QPainter *painter) override;

private:
    static VectorDataCurrent calc3WireVectorData(const VectorDataCurrent &currentData);
    void adjustAngleSettings(const VectorDataCurrent& currentVectors);
    void calcAndSetMaxValues(const VectorDataCurrent& currentVectors);

    std::shared_ptr<VectorSettings> m_vectorSettings;

    QVector<QColor> m_inVectorColors = QVector<QColor>(VectorConstants::COUNT_VECTORS);
    QVector<QString> m_inVectorLabels = QVector<QString>(VectorConstants::COUNT_VECTORS);
    QVector<QVector2D> m_inVectors = QVector<QVector2D>(VectorConstants::COUNT_VECTORS);
};

#endif // VECTORPAINTCONTROLLER_H
