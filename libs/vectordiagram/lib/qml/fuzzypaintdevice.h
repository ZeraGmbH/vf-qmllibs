#ifndef FUZZYPAINTDEVICE_H
#define FUZZYPAINTDEVICE_H

#include "fuzzypaintengine.h"
#include <QPaintDevice>
#include <memory>

class FuzzyPaintDevice : public QPaintDevice
{
public:
    FuzzyPaintDevice(const QRect &boundingRect = QRect(0, 0, 100, 100));

    QByteArray getDataRecorded() const;

    QPaintEngine *paintEngine() const override;
    int metric(PaintDeviceMetric metric) const override;

private:
    std::unique_ptr<FuzzyPaintEngine> m_fuzzyEngine;
    QRect m_boundingRect;
};

#endif // FUZZYPAINTDEVICE_H
