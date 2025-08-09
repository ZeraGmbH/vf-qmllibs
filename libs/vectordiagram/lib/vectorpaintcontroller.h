#ifndef VECTORPAINTCONTROLLER_H
#define VECTORPAINTCONTROLLER_H

#include "vectorsettingsgeometry.h"
#include "vectorsettingsstatic.h"
#include <QColor>
#include <QVector>
#include <QVector2D>
#include <QSet>

class VectorPaintController
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
    void setMaxOvershootFactor(float maxOvershoot);

    void setNominalVoltage(float nomVoltage);
    void setMinVoltage(float minVoltage);

    void setNominalCurrent(float nomCurrent);
    void setMinCurrent(float minCurrent);

    void setGridVisible(bool gridVisible);
    void setGridColor(const QColor& gridColor);
    void setCircleVisible(bool circleVisible);
    void setCircleColor(const QColor& circleColor);

    void setVectorLabel(int idx, const QString &vectorLabel);
    void setVectorColor(int idx, const QColor &vectorColor);

    void setVector(int idx, const QVector2D &vector);

    void paint(QPainter *painter);

private:
    void drawCoordCross(QPainter *painter);
    void drawCircle(QPainter* painter);
    void drawVectorLine(QPainter *painter, float nomValue, const QVector2D &value, const QColor &color);
    void drawArrowHead(QPainter *painter, float nomValue, const QVector2D &value, const QColor &color);

    QVector2D calcPixVec(QPainter *painter, float nomValue, const QVector2D &value, float shortenPixels = 0.0);

    // API
    VectorSettingsGeometry m_settingsGeometry;
    VectorType m_vectorType = VectorType::VIEW_STAR;
    bool m_gridVisible = true;
    QColor m_gridColor = Qt::darkGray;
    bool m_circleVisible = true;
    QColor m_circleColor = Qt::darkGray;
    QVector<QColor> m_vectorColor = QVector<QColor>(VectorSettingsStatic::COUNT_VECTORS);
    QVector<QString> m_vectorLabel = QVector<QString>(VectorSettingsStatic::COUNT_VECTORS);

    bool m_forceI1Top = true;

    QVector<QVector2D> m_vector = QVector<QVector2D>(VectorSettingsStatic::COUNT_VECTORS);

};

#endif // VECTORPAINTCONTROLLER_H
