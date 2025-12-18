#ifndef FUZZYPAINTDEVICE_H
#define FUZZYPAINTDEVICE_H

#include "fuzzypaintengine.h"
#include <QPaintDevice>
#include <memory>

class FuzzyPaintDevice : public QPaintDevice
{
public:
    FuzzyPaintDevice();

    QByteArray getDataRecorded() const;

    QPaintEngine *paintEngine() const override;
    int metric(PaintDeviceMetric metric) const override;

private:
    std::unique_ptr<FuzzyPaintEngine> m_fuzzyEngine;
    QRect m_boundingRect;
};

#endif // FUZZYPAINTDEVICE_H
