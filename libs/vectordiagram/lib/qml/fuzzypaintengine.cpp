#include "fuzzypaintengine.h"
#include <QPainterPath>

FuzzyPaintEngine::FuzzyPaintEngine() :
    QPaintEngine(AllFeatures)
{
}

QByteArray FuzzyPaintEngine::getDataRecorded() const
{
    if (m_streamedByteArray == nullptr)
        return QByteArray();
    qWarning("Fuzzy size: %i", m_streamedByteArray->size());
    return *m_streamedByteArray;
}

bool FuzzyPaintEngine::begin(QPaintDevice *pdev)
{
    Q_UNUSED(pdev);
    m_streamedByteArray = std::make_unique<QByteArray>();
    m_dataBuffer = std::make_unique<QBuffer>(m_streamedByteArray.get());
    m_dataBuffer->open(QIODevice::WriteOnly);
    m_dataStream = std::make_unique<QDataStream>(m_dataBuffer.get());
    m_dataStream->setFloatingPointPrecision(QDataStream::SinglePrecision);
    setActive(true);
    return true;
}

bool FuzzyPaintEngine::end()
{
    m_dataBuffer->close();
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
        *m_dataStream << state.pen().color(); // reduce to minimum
    if (state.state() & DirtyFont) {
        QFont font = state.font();
        *m_dataStream << reducePrecision(font.pixelSize());
        *m_dataStream << font.family().toLocal8Bit();
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
    *m_dataStream << reducePrecision(rect.x());
    *m_dataStream << reducePrecision(rect.y());
    *m_dataStream << reducePrecision(rect.width());
    *m_dataStream << reducePrecision(rect.height());
}

void FuzzyPaintEngine::drawLines(const QLineF *lines, int lineCount)
{
    for (int lineNo=0; lineNo<lineCount; lineNo++) {
        *m_dataStream << reducePrecision(lines[lineNo].x1());
        *m_dataStream << reducePrecision(lines[lineNo].x2());
        *m_dataStream << reducePrecision(lines[lineNo].y1());
        *m_dataStream << reducePrecision(lines[lineNo].y2());
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
        *m_dataStream << reducePrecision(points[point].x());
        *m_dataStream << reducePrecision(points[point].y());
    }
    *m_dataStream << reducePrecision(mode);
}

void FuzzyPaintEngine::drawRects(const QRectF *rects, int rectCount)
{
    for (int rectNo=0; rectNo<rectCount; rectNo++) {
        const QRectF &rect = rects[rectNo];
        *m_dataStream << reducePrecision(rect.x());
        *m_dataStream << reducePrecision(rect.y());
        *m_dataStream << reducePrecision(rect.width());
        *m_dataStream << reducePrecision(rect.height());
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
        *m_dataStream << reducePrecision(elem.type);
        *m_dataStream << reducePrecision(elem.x);
        *m_dataStream << reducePrecision(elem.y);
    }*/
}

void FuzzyPaintEngine::calledButDataIgnored()
{
}
