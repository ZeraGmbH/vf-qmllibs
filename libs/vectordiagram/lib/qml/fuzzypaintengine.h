#ifndef FUZZYPAINTENGINE_H
#define FUZZYPAINTENGINE_H

#include <QPaintEngine>
#include <QByteArray>
#include <QBuffer>
#include <QDataStream>
#include <memory>

class FuzzyPaintEngine : public QPaintEngine
{
public:
    FuzzyPaintEngine();
    QByteArray getDataRecorded() const;

    bool begin(QPaintDevice *pdev) override;
    bool end() override;
    void updateState(const QPaintEngineState &state) override;
    QPaintEngine::Type type() const override;

    void drawEllipse(const QRectF &rect) override;
    void drawLines(const QLineF *lines, int lineCount) override;
    void drawPath(const QPainterPath &path) override;

    // How to avoid call of this???
    void drawImage(const QRectF &rectangle,
                   const QImage &image,
                   const QRectF &sr,
                   Qt::ImageConversionFlags flags) override;
    void drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr) override;

    void drawPoints(const QPointF *points, int pointCount) override;
    void drawPolygon(const QPointF *points, int pointCount, QPaintEngine::PolygonDrawMode mode) override;

private:
    std::unique_ptr<QByteArray> m_streamedByteArray;
    std::unique_ptr<QBuffer> m_dataBuffer;
    std::unique_ptr<QDataStream> m_dataStream;
};

#endif // FUZZYPAINTENGINE_H
