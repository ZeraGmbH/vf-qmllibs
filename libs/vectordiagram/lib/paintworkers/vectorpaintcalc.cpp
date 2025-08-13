#include "vectorpaintcalc.h"

int VectorPaintCalc::getHeight(const QPainter *painter)
{
    QPaintDevice *paintDevice = painter->device();
    if (paintDevice)
        return paintDevice->height();
    return 1;
}

int VectorPaintCalc::getWidth(const QPainter *painter)
{
    QPaintDevice *paintDevice = painter->device();
    if (paintDevice)
        return paintDevice->width();
    return 1;
}

float VectorPaintCalc::centerX(const QPainter *painter)
{
    return getWidth(painter) / 2;
}

float VectorPaintCalc::centerY(const QPainter *painter)
{
    return getHeight(painter) / 2;
}

float VectorPaintCalc::getClipSquareLen(const QPainter *painter)
{
    const float w = getWidth(painter);
    const float h = getHeight(painter);
    return std::min(h, w);
}

QVector2D VectorPaintCalc::calcVectorOtherLen(const QVector2D &vector, float len)
{
    const float origLen = vector.length();
    const float mult = len / origLen;
    QVector2D resultVector(
        vector.x() * mult,
        vector.y() * mult);
    return resultVector;
}

QVector2D VectorPaintCalc::calcPixVec(QPainter *painter, const VectorSettingsEx &vectorSettingsEx,
                                      const QVector2D &value, float shorten)
{
    const VectorSettings &vectorSetttings = vectorSettingsEx.vectorSetttings;
    const float angle = atan2(value.y(), value.x()) + vectorSetttings.m_angles.getOffsetAngle();
    const float nomRadius = vectorSetttings.m_lengths.getVectorLenNominalInPixels(painter);
    const float nomValue = vectorSetttings.m_lengths.getNomOrMaxValue(vectorSettingsEx.vectorType);
    const float vectLenPixels = nomRadius * value.length() / nomValue - shorten;
    const float directionFactor =
        // y on screen increases downwards => Mathematical <=> -1.0
        vectorSetttings.m_angles.getRotationDirection() == VectorSettingsAngles::Mathematical ? -1.0 : 1.0;
    QVector2D resultVector(
        vectLenPixels * cos(angle),
        vectLenPixels * sin(angle) * directionFactor);
    return resultVector;
}
