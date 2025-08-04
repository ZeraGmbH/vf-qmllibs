#ifndef VECTORPAINTER_H
#define VECTORPAINTER_H

#include <QColor>
#include <QVector>
#include <QPainter>
#include <QVector2D>
#include <QSet>

class VectorPainter
{
public:
    ~VectorPainter() = default;

    static constexpr int COUNT_PHASES = 3;
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
    void drawGrid(QPainter *painter);
    void drawCircle(QPainter* painter);

    static int height(const QPainter *painter);
    static int width(const QPainter *painter);

    float getClipSquareLen(const QPainter *painter);
    float getGridAndCircleLineWidth(const QPainter *painter);
    float getVectorLenMaxInPixels(const QPainter *painter);
    float getVectorLenNominalInPixels(const QPainter *painter);


    // API
    float m_phiOrigin = 0.0;
    float m_nomVoltage = 0.0;
    float m_minVoltage = 0.0;
    float m_nomCurrent = 0.0;
    float m_minCurrent = 0.0;
    VectorType m_vectorType = VectorType::VIEW_STAR;
    bool m_gridVisible = true;
    QColor m_gridColor = Qt::darkGray;
    bool m_circleVisible = true;
    QColor m_circleColor = Qt::darkGray;
    float m_maxOvershoot = 1.25;
    QVector<QColor> m_vectorColor = QVector<QColor>(COUNT_PHASES*2);
    QVector<QString> m_vectorLabel = QVector<QString>(COUNT_PHASES*2);

    bool m_forceI1Top = true;

    QVector<QVector2D> m_vector = QVector<QVector2D>(COUNT_PHASES*2);

    // internal
    float m_fromX = 0.0;
    float m_fromY = 0.0;
    void setFontForLabels(QPainter *painter);
};

#endif // VECTORPAINTER_H
