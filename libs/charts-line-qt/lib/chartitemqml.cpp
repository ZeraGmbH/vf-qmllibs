#include "chartitemqml.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QGraphicsScene>
#include <QPainter>

ChartItemQml::ChartItemQml(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    setAntialiasing(true);
    setupDemoChart();
}

void ChartItemQml::setupDemoChart()
{
    auto *seriesLeft  = new QLineSeries(&m_chart);
    seriesLeft->setName(QStringLiteral("Left axis data"));
    seriesLeft->append(0.0, 0.0);
    seriesLeft->append(1.0, 2.0);
    seriesLeft->append(2.0, 3.0);
    seriesLeft->append(3.0, 2.5);
    seriesLeft->append(4.0, 5.0);

    auto *seriesRight = new QLineSeries(&m_chart);
    seriesRight->setName(QStringLiteral("Right axis data"));
    seriesRight->append(0.0, 10.0);
    seriesRight->append(1.0, 20.0);
    seriesRight->append(2.0, 18.0);
    seriesRight->append(3.0, 25.0);
    seriesRight->append(4.0, 40.0);

    m_chart.addSeries(seriesLeft);
    m_chart.addSeries(seriesRight);
    m_chart.setTitle(QStringLiteral("Dual Y axis (QML)"));

    auto *axisX = new QValueAxis(&m_chart);
    axisX->setTitleText(QStringLiteral("X"));
    axisX->setLabelFormat("%.1f");
    axisX->setTickCount(5);
    m_chart.addAxis(axisX, Qt::AlignBottom);

    auto *axisYLeft = new QValueAxis(&m_chart);
    axisYLeft->setLabelsVisible(false);
    axisYLeft->setTitleText(QStringLiteral("Left Y"));
    axisYLeft->setTickCount(6);
    m_chart.addAxis(axisYLeft, Qt::AlignLeft);

    auto *axisYRight = new QValueAxis(&m_chart);
    axisYRight->setTitleText(QStringLiteral("Right Y"));
    axisYLeft->setLabelsVisible(false);
    axisYRight->setTickCount(6);
    m_chart.addAxis(axisYRight, Qt::AlignRight);

    seriesLeft->attachAxis(axisX);
    seriesLeft->attachAxis(axisYLeft);

    seriesRight->attachAxis(axisX);
    seriesRight->attachAxis(axisYRight);
}

void ChartItemQml::drawLabels(QPainter *painter)
{
    // 2) Custom Y-axis labels (example for left axis)
    auto *axisY = qobject_cast<QValueAxis *>(m_chart.axisY());
    auto *axisX = qobject_cast<QValueAxis *>(m_chart.axisX());
    if (!axisY || !axisX)
        return;

    const QRectF plotArea = m_chart.plotArea();

    const int tickCount = axisY->tickCount();
    if (tickCount < 2)
        return;

    const double minY = axisY->min();
    const double maxY = axisY->max();

    painter->save();
    painter->setPen(Qt::black);
    QFont f = painter->font();
    f.setPointSize(10);
    painter->setFont(f);

    for (int i = 0; i < tickCount; ++i) {
        // Axis value at this tick
        double v = minY + (maxY - minY) * i / (tickCount - 1);

        // Value scaling: show in kV
        double scaled = v / 1000.0;
        QString text = QString::number(scaled, 'f', 2); // e.g. "1.23"
        text += QLatin1String(" kV");

        // Map to pixel Y in plot area: linear mapping minY..maxY -> plotArea.bottom..top
        const double t = (v - minY) / (maxY - minY);
        const qreal y = plotArea.bottom() - t * plotArea.height();

        // Draw at left of plot area with some margin
        const qreal x = plotArea.left() - 8; // 8 px gap from plot area
        painter->drawText(QPointF(x, y + 4), text); // +4 for baseline alignment
    }
    painter->restore();
}

void ChartItemQml::paint(QPainter *painter)
{
    // Render chart into the item's rect
    const QRectF rect = boundingRect();
    m_chart.resize(rect.size().toSize());
    m_chart.scene()->render(painter, rect, QRectF(QPointF(0, 0), m_chart.size()));
}
