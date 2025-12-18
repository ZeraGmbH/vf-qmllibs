#include "fuzzypaintengine.h"
#include <QPainterPath>

FuzzyPaintEngine::FuzzyPaintEngine() :
    QPaintEngine(AllFeatures)
{
}

quint32 FuzzyPaintEngine::getCrc32() const
{
    if (m_crcBuffer == nullptr)
        return PseudoCrcBuffer::InitialCrc;
    return m_crcBuffer->getCrc();
}

bool FuzzyPaintEngine::begin(QPaintDevice *pdev)
{
    Q_UNUSED(pdev);
    m_crcBuffer = std::make_unique<PseudoCrcBuffer>();
    m_crcBuffer->open(QIODevice::WriteOnly);
    m_stream = std::make_unique<QDataStream>(m_crcBuffer.get());
    m_stream->setFloatingPointPrecision(QDataStream::SinglePrecision);
    setActive(true);
    return true;
}

bool FuzzyPaintEngine::end()
{
    m_crcBuffer->close();
    setActive(false);
    return true;
}

#define PRECISION_TYPE qint8

PRECISION_TYPE reducePrecision(float x)
{
    int val = qRound(x);
    val = std::min(val, int(std::numeric_limits<PRECISION_TYPE>::max()));
    val = std::max(val, int(std::numeric_limits<PRECISION_TYPE>::min()));
    return val;
}

void FuzzyPaintEngine::updateState(const QPaintEngineState &state)
{
    if (state.state() & DirtyPen)
        *m_stream << state.pen().color(); // reduce to minimum
    if (state.state() & DirtyFont) {
        QFont font = state.font();
        *m_stream << reducePrecision(font.pixelSize());
        *m_stream << font.family().toLocal8Bit();
    }
    if (state.state() & DirtyBrush)
        // Brush is not fuzzy yet
        calledButDataIgnored();
    if (state.state() & DirtyTransform)
        calledButDataIgnored();
    if (state.state() & DirtyHints)
        calledButDataIgnored();
    if (state.state() & DirtyClipRegion)
        calledButDataIgnored();
    if (state.state() & DirtyClipEnabled)
        calledButDataIgnored();
    if (state.state() & DirtyClipPath)
        calledButDataIgnored();

    ////////////////////
    // not called in our use cases (yet)
    if (state.state() & DirtyBrushOrigin)
        qWarning("Unhandled DirtyBrushOrigin");
    if (state.state() & DirtyBackground)
        qWarning("Unhandled DirtyBackground");
    if (state.state() & DirtyBackgroundMode)
        qWarning("Unhandled DirtyBackgroundMode");
    if (state.state() & DirtyCompositionMode)
        qWarning("Unhandled DirtyCompositionMode");
    if (state.state() & DirtyOpacity)
        qWarning("Unhandled DirtyOpacity");
}

QPaintEngine::Type FuzzyPaintEngine::type() const
{
    return QPaintEngine::User;
}

void FuzzyPaintEngine::drawEllipse(const QRectF &rect)
{
    *m_stream << reducePrecision(rect.x());
    *m_stream << reducePrecision(rect.y());
    *m_stream << reducePrecision(rect.width());
    *m_stream << reducePrecision(rect.height());
}

void FuzzyPaintEngine::drawLines(const QLineF *lines, int lineCount)
{
    for (int lineNo=0; lineNo<lineCount; lineNo++) {
        *m_stream << reducePrecision(lines[lineNo].x1());
        *m_stream << reducePrecision(lines[lineNo].x2());
        *m_stream << reducePrecision(lines[lineNo].y1());
        *m_stream << reducePrecision(lines[lineNo].y2());
    }
}

void FuzzyPaintEngine::drawPath(const QPainterPath &path)
{
    storePaintPath(path);
}

void FuzzyPaintEngine::drawImage(const QRectF &rectangle,
                                 const QImage &image,
                                 const QRectF &sr,
                                 Qt::ImageConversionFlags flags)
{
    Q_UNUSED(rectangle)
    Q_UNUSED(image)
    Q_UNUSED(sr)
    Q_UNUSED(flags)
    qWarning("Unhandled drawImage");
}

void FuzzyPaintEngine::drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr)
{
    Q_UNUSED(r)
    Q_UNUSED(pm)
    Q_UNUSED(sr)
    qWarning("Unhandled drawPixmap");
}

void FuzzyPaintEngine::drawPoints(const QPointF *points, int pointCount)
{
    Q_UNUSED(points)
    Q_UNUSED(pointCount)
    qWarning("Unhandled drawPoints");
}

void FuzzyPaintEngine::drawPolygon(const QPointF *points, int pointCount, PolygonDrawMode mode)
{
    for (int point=0; point<pointCount; point++) {
        *m_stream << reducePrecision(points[point].x());
        *m_stream << reducePrecision(points[point].y());
    }
    *m_stream << reducePrecision(mode);
}

void FuzzyPaintEngine::drawRects(const QRectF *rects, int rectCount)
{
    for (int rectNo=0; rectNo<rectCount; rectNo++) {
        const QRectF &rect = rects[rectNo];
        *m_stream << reducePrecision(rect.x());
        *m_stream << reducePrecision(rect.y());
        *m_stream << reducePrecision(rect.width());
        *m_stream << reducePrecision(rect.height());
    }
}

void FuzzyPaintEngine::storePaintPath(const QPainterPath &path)
{
    Q_UNUSED(path)
    calledButDataIgnored();
    // This is big boy - learn if we can ignore it
    /*int elemCount = path.elementCount();
    for (int elemNo=0; elemNo<elemCount; ++elemNo) {
        QPainterPath::Element elem = path.elementAt(elemNo);
        *m_stream << reducePrecision(elem.type);
        *m_stream << reducePrecision(elem.x);
        *m_stream << reducePrecision(elem.y);
    }*/
}

void FuzzyPaintEngine::calledButDataIgnored()
{
}
