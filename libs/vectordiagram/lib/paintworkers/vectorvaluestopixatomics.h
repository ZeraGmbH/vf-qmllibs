#ifndef VECTORVALUESTOPIXATOMICS_H
#define VECTORVALUESTOPIXATOMICS_H

#include "vectorsettings.h"
#include <QVector>
#include <QList>
#include <QVector2D>
#include <QPainter>

struct VectorDataCurrent {
    QVector<QColor> m_colors;
    QVector<QString> m_label;
    QVector<QVector2D> m_vectorData;
};

class VectorValuesToPixAtomics
{
public:
    static bool drawVoltageStar(QPainter *painter, const VectorSettings &vectorSettings,
                                const VectorDataCurrent& currentVectors);
    static bool drawCurrentStar(QPainter *painter, const VectorSettings &vectorSettings,
                                const VectorDataCurrent& currentVectors);
    static bool drawPhasesStar(QPainter *painter, int startPhaseIdx, int endPhaseIdx,
                               const VectorSettings &vectorSettings, const VectorDataCurrent& currentVectors);
    static void drawVoltageTriangle(QPainter *painter, const VectorSettings &vectorSettings,
                                    const VectorDataCurrent& currentVectors);
    static void drawLabels(QPainter *painter, const VectorSettings &vectorSettings,
                           const VectorDataCurrent& currentVectors);
private:
    struct ShownLabel {
        QVector2D wantedPixLenLabel;
        int idx;
    };
    typedef QList<ShownLabel> ShownLabels;
    static ShownLabels getShownLabelsAndPixLenWanted(const QPainter *painter, const VectorSettings &vectorSettings,
                                                     const VectorDataCurrent& currentVectors);
    static QVector2D limitLabelVectorLen(const QPainter *painter, const QVector2D &pixLenVector, const QString &label);
    static QVector2D lengthenLabelTooShortVector(const QPainter *painter, const QVector2D &pixLenVector);
};

#endif // VECTORVALUESTOPIXATOMICS_H
