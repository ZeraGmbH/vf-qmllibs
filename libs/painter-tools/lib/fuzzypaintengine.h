#ifndef FUZZYPAINTENGINE_H
#define FUZZYPAINTENGINE_H

#include "pseudocrcbuffer.h"
#include <QPaintEngine>
#include <QByteArray>
#include <QDataStream>
#include <memory>

class FuzzyPaintEngine : public QPaintEngine
{
public:
    FuzzyPaintEngine();
    quint32 getCrc32() const;

    bool begin(QPaintDevice *pdev) override;
    bool end() override;
    void updateState(const QPaintEngineState &state) override;
    QPaintEngine::Type type() const override;

    void drawEllipse(const QRectF &rect) override;
    void drawLines(const QLineF *lines, int lineCount) override;
    void drawPath(const QPainterPath &path) override;

    void drawImage(const QRectF &rectangle,
                   const QImage &image,
                   const QRectF &sr,
                   Qt::ImageConversionFlags flags) override;
    void drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr) override;

    void drawPoints(const QPointF *points, int pointCount) override;
    void drawPolygon(const QPointF *points, int pointCount, QPaintEngine::PolygonDrawMode mode) override;
    void drawRects(const QRectF *rects, int rectCount) override;
private:
    void storePaintPath(const QPainterPath &path);
    void calledButDataIgnored();

    std::unique_ptr<PseudoCrcBuffer> m_crcBuffer;
    std::unique_ptr<QDataStream> m_stream;
};

#endif // FUZZYPAINTENGINE_H
