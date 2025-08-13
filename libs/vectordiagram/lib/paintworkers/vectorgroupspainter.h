#ifndef VECTORGROUPSPAINTER_H
#define VECTORGROUPSPAINTER_H

#include "vectorsettings.h"
#include <QVector>
#include <QVector2D>
#include <QPainter>

struct VectorDataCurrent {
    QVector<QColor> m_colors;
    QVector<QString> m_label;
    QVector<QVector2D> m_vectorData;
};

class VectorGroupsPainter
{
public:
    static bool drawVoltageStar(QPainter *painter,
                                const VectorSettings &vectorSettings, const VectorDataCurrent& currentVectors);
    static bool drawCurrentStar(QPainter *painter,
                                const VectorSettings &vectorSettings, const VectorDataCurrent& currentVectors);
    static bool drawPhasesStar(QPainter *painter, int startPhaseIdx, int endPhaseIdx,
                               const VectorSettings &vectorSettings, const VectorDataCurrent& currentVectors);
    static void drawVoltageTriangle(QPainter *painter, const VectorSettings &vectorSettings,
                                    const VectorDataCurrent& currentVectors);
    static void drawLabels(QPainter *painter, const VectorSettings &vectorSettings,
                           const VectorDataCurrent& currentVectors);
    static VectorDataCurrent calc3WireVectorData(const VectorDataCurrent &currentData);
};

#endif // VECTORGROUPSPAINTER_H
