#include "hpwbarchart.h"
#include "bardata.h"
#include "barscaledraw.h"
#include "sidescaledraw.h"
#include "fuzzypaintdevice.h"
#include <cmath>
#include <timerfactoryqt.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_barchart.h>
#include <qwt_column_symbol.h>
#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_engine.h>
#include <qwt_plot.h>
#include <qwt_scale_widget.h>
#include <qwt_text.h>

HpwBarChart::HpwBarChart(QQuickItem *t_parent):
    QQuickPaintedItem(t_parent),
    m_canvas(new QwtPlotCanvas()),
    m_plot(new QwtPlot()),
    m_barDataLeft(new BarData()), //cleaned up by the plot
    m_minValueLeftAxis(1.0)
{
    connect(this, SIGNAL(heightChanged()), this, SLOT(onHeightChanged()));
    connect(this, SIGNAL(widthChanged()), this, SLOT(onWidthChanged()));
    connect(this, SIGNAL(labelsChanged(QStringList)), this, SLOT(onLabelsChanged(QStringList)));

    m_plot->setAttribute(Qt::WA_NoSystemBackground);
    m_plot->setAutoFillBackground(true);

    m_canvas->setPaintAttribute(QwtPlotCanvas::BackingStore, false);
    m_canvas->setPaintAttribute(QwtPlotCanvas::Opaque, false);
    m_canvas->setLineWidth(1);
    m_canvas->setFrameStyle(QFrame::NoFrame);

    m_plot->setAxisScaleDraw(QwtPlot::yLeft, new SideScaleDraw()); //cleaned up by the plot
    m_plot->setAxisScaleDraw(QwtPlot::xBottom, new BarScaleDraw()); //cleaned up by the plot

    m_plot->setCanvas(m_canvas);

    m_barDataLeft->attach(m_plot);
    m_barDataLeft->setYAxis(QwtPlot::yLeft);
    m_barDataLeft->setBaseline(0.0);

    m_plot->setAutoReplot(true);
}

HpwBarChart::~HpwBarChart()
{
    delete m_canvas;
    delete m_plot;
}

bool HpwBarChart::bottomLabels() const
{
    return m_bottomLabelsEnabled;
}

bool HpwBarChart::legendEnabled() const
{
    return m_legendEnabled;
}

QColor HpwBarChart::bgColor() const
{
    return m_bgColor;
}

QColor HpwBarChart::borderColor() const
{
    return m_borderColor;
}

QColor HpwBarChart::textColor() const
{
    return m_textColor;
}

QString HpwBarChart::chartTitle() const
{
    return m_chartTitle;
}

void HpwBarChart::paint(QPainter *t_painter)
{
    m_plot->render(t_painter);
}

double HpwBarChart::maxValueLeftAxis() const
{
    return m_maxValueLeftAxis;
}

double HpwBarChart::minValueLeftAxis() const
{
    return m_minValueLeftAxis;
}

QColor HpwBarChart::colorLeftAxis() const
{
    return m_colorLeftAxis;
}

QString HpwBarChart::titleLeftAxis() const
{
    return m_plot->axisTitle(QwtPlot::yLeft).text();
}

void HpwBarChart::onExternValuesChanged()
{
    startUpdate();
}

void HpwBarChart::onHeightChanged()
{
    if(contentsBoundingRect().height()>0)
        m_plot->setFixedHeight(contentsBoundingRect().height());
    else
        m_plot->setFixedHeight(0);
}

void HpwBarChart::onWidthChanged()
{
    if(contentsBoundingRect().width()>0)
        m_plot->setFixedWidth(contentsBoundingRect().width());
    else
        m_plot->setFixedWidth(0);
}

void HpwBarChart::setBgColor(QColor t_backgroundColor)
{
    if (m_bgColor != t_backgroundColor) {
        QPalette p = m_plot->palette();
        p.setColor(QPalette::Window, t_backgroundColor);
        m_canvas->setPalette(p);
        m_bgColor = t_backgroundColor;
        emit bgColorChanged(t_backgroundColor);
        startUpdate();
    }
}

void HpwBarChart::setborderColor(QColor t_borderColor)
{
    if (m_borderColor != t_borderColor) {
        m_borderColor = t_borderColor;
        emit borderColorChanged(t_borderColor);
        startUpdate();
    }
}

void HpwBarChart::useBottomLabels(bool t_labelsEnabled)
{
    m_bottomLabelsEnabled=t_labelsEnabled;
    if(t_labelsEnabled) {
        m_plot->setAxisScaleDraw(QwtPlot::xBottom, new BarScaleDraw(Qt::Vertical, m_bottomLabels)); //cleaned up by the plot
        m_plot->setAxisMaxMajor(QwtPlot::xBottom, m_bottomLabels.count());
    }
    else {
        m_bottomLabels.clear();
        m_plot->setAxisScaleDraw(QwtPlot::xBottom, new BarScaleDraw(Qt::Vertical, {})); //cleaned up by the plot
    }
}

void HpwBarChart::setChartTitle(QString t_chartTitle)
{
    if (m_chartTitle != t_chartTitle) {
        m_chartTitle = t_chartTitle;
        m_plot->setTitle(t_chartTitle);
    }
}

void HpwBarChart::setLegendEnabled(bool t_legendEnabled)
{
    if(t_legendEnabled!=m_legendEnabled) {
        if(t_legendEnabled) {
            QwtLegend *tmpLegend = new QwtLegend(); //cleaned up by the plot
            QPalette tmpPa;
            tmpPa.setColor(QPalette::Text, t_legendEnabled);
            tmpPa.setColor(QPalette::WindowText, t_legendEnabled);
            tmpPa.setColor(QPalette::Window, Qt::transparent);
            tmpPa.setColor(QPalette::Base, Qt::transparent);

            tmpLegend->setPalette(tmpPa);
            m_plot->insertLegend(tmpLegend);
        }
        else
            m_plot->insertLegend(nullptr);
    }
    m_legendEnabled=t_legendEnabled;
}

void HpwBarChart::setTextColor(QColor t_textColor)
{
    if(t_textColor != m_textColor) {
        BarScaleDraw *tmpScaleX;
        QPalette tmpPa;
        tmpPa.setColor(QPalette::Text, t_textColor);
        tmpPa.setColor(QPalette::WindowText, t_textColor);
        tmpPa.setColor(QPalette::Window, Qt::transparent);
        tmpPa.setColor(QPalette::Base, Qt::transparent);

        m_plot->setPalette(tmpPa);
        if(m_plot->legend())
            m_plot->legend()->setPalette(tmpPa);

        m_plot->axisWidget(QwtPlot::xBottom)->setPalette(tmpPa);

        tmpScaleX=new BarScaleDraw(); //cleaned up by the plot
        tmpScaleX->setColor(t_textColor);

        ///todo check if this is necessary since the palette was set previously
        m_plot->setAxisScaleDraw(QwtPlot::xBottom, tmpScaleX);

        labelsChanged(m_bottomLabels);
    }

    m_textColor = t_textColor;
}

void HpwBarChart::setMaxValueLeftAxis(double t_maxValue)
{
    m_plot->setAxisScale(QwtPlot::yLeft, m_minValueLeftAxis, t_maxValue);
    m_maxValueLeftAxis = t_maxValue;
    m_barDataLeft->setBaseline(0.0);
}

void HpwBarChart::setMinValueLeftAxis(double t_minValue)
{
    m_plot->setAxisScale(QwtPlot::yLeft, t_minValue, m_maxValueLeftAxis);
    m_minValueLeftAxis = t_minValue;
    m_barDataLeft->setBaseline(0.0);
}

void HpwBarChart::setColorLeftAxis(QColor t_color)
{
    QPalette tmpPa;
    tmpPa.setColor(QPalette::Text, t_color);
    tmpPa.setColor(QPalette::WindowText, t_color);
    tmpPa.setColor(QPalette::Window, Qt::transparent);
    tmpPa.setColor(QPalette::Base, Qt::transparent);

    m_plot->axisWidget(QwtPlot::yLeft)->setPalette(tmpPa);
    m_colorLeftAxis = t_color;
}

void HpwBarChart::setTitleLeftAxis(QString t_title)
{
    m_plot->setAxisTitle(QwtPlot::yLeft, t_title);
}

void HpwBarChart::onLabelsChanged(QStringList t_labels)
{
    m_bottomLabels=t_labels;
    useBottomLabels(m_bottomLabelsEnabled);
}

void HpwBarChart::setPValues(QList<double> t_pValues)
{
    m_pValues = avoidZeroArtifacts(t_pValues);
    onExternValuesChanged();
}

void HpwBarChart::setQValues(QList<double> t_qValues)
{
    m_qValues = avoidZeroArtifacts(t_qValues);
    onExternValuesChanged();
}

void HpwBarChart::setSValues(QList<double> t_sValues)
{
    m_sValues = avoidZeroArtifacts(t_sValues);
    onExternValuesChanged();
}

void HpwBarChart::onUpdateTimer()
{
    m_plot->updateGeometry();
    m_plot->updateAxes();
    m_plot->updateLegend();
    m_plot->updateLayout();
    m_plot->updateCanvasMargins();

    updateBarsAndLegends();

    FuzzyPaintDevice fuzzyPaintDev;
    QPainter testPainter;
    testPainter.begin(&fuzzyPaintDev);
    m_plot->render(&testPainter);
    testPainter.end();

    quint32 newCrc = fuzzyPaintDev.getCrc32();
    if (m_lastPaintCrc != newCrc) {
        m_lastPaintCrc = newCrc;
        update();
    }
}

void HpwBarChart::startUpdate()
{
    m_updateTimer = TimerFactoryQt::createSingleShot(10);
    connect(m_updateTimer.get(), &TimerTemplateQt::sigExpired,
            this, &HpwBarChart::onUpdateTimer);
    m_updateTimer->start();
}

void HpwBarChart::updateBarsAndLegends()
{
    QVector<double> tmpSamples;
    if (m_pValues.count()>0 && m_qValues.count()>0 && m_sValues.count()>0 &&
        m_pValues.count() == m_qValues.count() && m_pValues.count() == m_sValues.count()) {
        // m_valuesLeftAxis is a list of P Q S values
        int tmpLeftBarCount = m_pValues.count() + m_qValues.count() + m_sValues.count();
        m_barDataLeft->clearData();
        int t_barCount=41;
        for(int i=0; i<t_barCount; ++i) {
            m_barDataLeft->addData(m_colorLeftAxis, QString::number(i));
            m_barDataLeft->addData(m_colorLeftAxis, QString(" "));
            m_barDataLeft->addData(m_colorLeftAxis, QString(" "));
        }

        for(int sampleCount = 0; sampleCount < tmpLeftBarCount/3; ++sampleCount) {
            tmpSamples.append(m_pValues.at(sampleCount));
            tmpSamples.append(m_qValues.at(sampleCount));
            tmpSamples.append(m_sValues.at(sampleCount));
        }

        if(m_legendEnabled)
            m_plot->insertLegend(new QwtLegend()); //cleaned up by the plot
        labelsChanged(m_barDataLeft->getTitles());
    }
    m_barDataLeft->setSamples(tmpSamples);
}

QList<double> HpwBarChart::avoidZeroArtifacts(const QList<double> &values)
{
    QList<double> adjustedValues;
    // optical tests: below is no change in value detectable
    const double minValue = fabs(m_minValueLeftAxis-m_maxValueLeftAxis) / 500.0;
    for (const double &value : values) {
        if(fabs(value) > minValue)
            adjustedValues.append(value);
        else
            adjustedValues.append(0.0);
    }
    return adjustedValues;
}
