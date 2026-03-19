#ifndef FFTBARCHART_H
#define FFTBARCHART_H

#include "pseudocrcbuffer.h"
#include <timertemplateqt.h>
#include <QQuickPaintedItem>
#include <QList>
#include <QColor>
#include <QString>

class QwtPlot;
class BarData;
class QwtPlotCanvas;
class VeinEntity;


/**
 * @brief Zera specific crap class to display hyperstyled FFT bar charts
 * @todo Replace with Qt Quick Charts once the perfomance is above mediocre
 */
class FftBarChart : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(FftBarChart)

    Q_PROPERTY(bool bottomLabelsEnabled READ bottomLabels WRITE useBottomLabels NOTIFY labelsChanged)
    Q_PROPERTY(bool legendEnabled READ legendEnabled WRITE setLegendEnabled)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setborderColor NOTIFY borderColorChanged)
    Q_PROPERTY(QColor color READ bgColor WRITE setBgColor NOTIFY bgColorChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Q_PROPERTY(QString chartTitle READ chartTitle WRITE setChartTitle)

    //left axis
    Q_PROPERTY(bool logScaleLeftAxis READ logScaleLeftAxis WRITE setLogScaleLeftAxis)
    Q_PROPERTY(double maxValueLeftAxis READ maxValueLeftAxis WRITE setMaxValueLeftAxis)
    Q_PROPERTY(double minValueLeftAxis READ minValueLeftAxis WRITE setMinValueLeftAxis)
    Q_PROPERTY(QColor colorLeftAxis READ colorLeftAxis WRITE setColorLeftAxis)
    Q_PROPERTY(QString titleLeftAxis READ titleLeftAxis WRITE setTitleLeftAxis)
    Q_PROPERTY(QVariant leftValue READ fooDummy WRITE onLeftValueChanged) //writeonly

    //right axis
    Q_PROPERTY(bool logScaleRightAxis READ logScaleRightAxis WRITE setLogScaleRightAxis)
    Q_PROPERTY(double maxValueRightAxis READ maxValueRightAxis WRITE setMaxValueRightAxis)
    Q_PROPERTY(double minValueRightAxis READ minValueRightAxis WRITE setMinValueRightAxis)
    Q_PROPERTY(QColor colorRightAxis READ colorRightAxis WRITE setColorRightAxis)
    Q_PROPERTY(bool rightAxisEnabled READ rightAxisEnabled WRITE setRightAxisEnabled)
    Q_PROPERTY(QString titleRightAxis READ titleRightAxis WRITE setTitleRightAxis)
    Q_PROPERTY(QVariant rightValue READ fooDummy WRITE onRightValueChanged) //writeonly

public:
    FftBarChart(QQuickItem *t_parent = 0);
    ~FftBarChart();

    bool bottomLabels() const;
    bool legendEnabled() const;

    QColor bgColor() const;
    QColor borderColor() const;
    QColor textColor() const;
    QString chartTitle() const;

    void paint(QPainter *t_painter) override;

    /**
    * @b redeclared to prevent calling QQuickItem::classBegin()
    */
    void classBegin() override {}

    //we really need support for writeonly properties
    QVariant fooDummy() const { return QVariant(); }

    //left axis
    bool logScaleLeftAxis() const;
    double maxValueLeftAxis() const;
    double minValueLeftAxis() const;
    QColor colorLeftAxis() const;
    QString titleLeftAxis() const;

    //right axis
    bool logScaleRightAxis() const;
    double maxValueRightAxis() const;
    double minValueRightAxis() const;
    QColor colorRightAxis() const;
    bool rightAxisEnabled() const;
    QString titleRightAxis() const;

public slots:
    void onExternValuesChanged();
    void onHeightChanged();
    void onWidthChanged();
    void setBgColor(const QColor &backgroundColor);
    void setborderColor(const QColor &borderColor);
    void useBottomLabels(bool labelsEnabled);
    void setChartTitle(const QString &chartTitle);
    void setLegendEnabled(bool legendEnabled);
    void setTextColor(const QColor &textColor);

    //left axis
    void setLogScaleLeftAxis(bool useLogScale);
    void setMaxValueLeftAxis(double maxValue);
    void setMinValueLeftAxis(double minValue);
    void setColorLeftAxis(const QColor &color);
    void setTitleLeftAxis(const QString &title);
    void onLeftValueChanged(const QVariant &leftValue);

    //right axis
    void setLogScaleRightAxis(bool useLogScale);
    void setMaxValueRightAxis(double maxValue);
    void setMinValueRightAxis(double minValue);
    void setColorRightAxis(const QColor &color);
    void setTitleRightAxis(const QString &title);
    void setRightAxisEnabled(bool rightAxisEnabled);
    void onRightValueChanged(const QVariant &rightValue);

signals:
    void bgColorChanged(const QColor &backgroundColor);
    void borderColorChanged(const QColor borderColor);
    void labelsChanged(const QStringList &labelsEnabled);
    void maxValueLeftAxisChanged(double maxValueLeftAxis);
    void minValueChanged(double minValue);

private slots:
    void onUpdateTimer();
    void onLabelsChanged(const QStringList &labels);

private:
    void startUpdate();
    void updateBarsAndLegends();

    TimerTemplateQtPtr m_updateTimer;
    quint32 m_lastPaintCrc = PseudoCrcBuffer::InitialCrc;
    bool m_bottomLabelsEnabled;
    bool m_legendEnabled;

    QColor m_bgColor;
    QColor m_borderColor;
    QColor m_textColor;
    QStringList m_bottomLabels;
    QString m_chartTitle;
    QwtPlotCanvas *m_canvas;
    QwtPlot *m_plot;

    //left axis
    bool m_logScaleLeftAxis = false;
    BarData *m_barDataLeft;
    double m_maxValueLeftAxis = 0.0;
    double m_minValueLeftAxis = 0.0;
    QList<qreal> m_valuesLeftAxis;
    QColor m_colorLeftAxis;

    //right axis
    bool m_logScaleRightAxis = false;
    BarData *m_barDataRight;
    double m_maxValueRightAxis = 0.0;
    double m_minValueRightAxis = 0.0;
    QList<qreal> m_valuesRightAxis;
    QColor m_colorRightAxis;

};

#endif // FFTBARCHART_H
