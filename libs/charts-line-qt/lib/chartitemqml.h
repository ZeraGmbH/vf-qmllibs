#include <QQuickPaintedItem>
#include <QtCharts/QChart>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
using namespace QtCharts;
#endif

class ChartItemQml : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit ChartItemQml(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

    Q_INVOKABLE void setupDemoChart();  // or expose properties / slots

    QChart *chart() { return &m_chart; }

private:
    void drawLabels(QPainter *painter);

    QChart m_chart;
};
