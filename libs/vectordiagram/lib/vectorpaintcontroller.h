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

    // enums must be in sync to PhasorDiagram::VectorType - suggestions?
    enum class VectorStandard : int
    {
        DIN,
        IEC,
        ANSI
    };
    void setVectorStandard(VectorStandard vectorStandard);
    VectorStandard getVectorStandard() const;

    enum class VectorType : int
    {
        VIEW_STAR = 0,
        VIEW_TRIANGLE = 1,
        VIEW_THREE_PHASE = 2
    };
    void setVectorType(VectorType vectorType);
    VectorType getVectorType() const;

    VectorSettings* getVectorSettings();

    void setVectorLabel(int idx, const QString &vectorLabel);
    void setVectorColor(int idx, const QColor &vectorColor);

    void setVector(int idx, const QVector2D &vector);

    void paint(QPainter *painter) override;

private:
    void adjustAngleSettings(const VectorDataCurrent& currentVectors);
    void calcAndSetMaxValues(const VectorDataCurrent& currentVectors);

    VectorSettings m_vectorSettings;
    VectorType m_vectorType = VectorType::VIEW_STAR;
    VectorStandard m_vectorStandard = VectorStandard::DIN;

    QVector<QColor> m_inVectorColors = QVector<QColor>(VectorConstants::COUNT_VECTORS);
    QVector<QString> m_inVectorLabels = QVector<QString>(VectorConstants::COUNT_VECTORS);
    QVector<QVector2D> m_inVectors = QVector<QVector2D>(VectorConstants::COUNT_VECTORS);
};

#endif // VECTORPAINTCONTROLLER_H
