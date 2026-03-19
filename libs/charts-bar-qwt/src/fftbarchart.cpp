#include "fftbarchart.h"
#include "bardata.h"
#include "barscaledraw.h"
#include "sidescaledraw.h"
#include "fuzzypaintdevice.h"
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


FftBarChart::FftBarChart(QQuickItem *t_parent):
    QQuickPaintedItem(t_parent),
    m_canvas(new QwtPlotCanvas()),
    m_plot(new QwtPlot()),
    m_barDataLeft(new BarData()), //cleaned up by the plot
    m_minValueLeftAxis(1.0),
    m_barDataRight(new BarData()), //cleaned up by the plot
    m_minValueRightAxis(1.0)
{
    connect(this, SIGNAL(heightChanged()), this, SLOT(onHeightChanged()));
    connect(this, SIGNAL(widthChanged()), this, SLOT(onWidthChanged()));
    connect(this, SIGNAL(labelsChanged(QStringList)), this, SLOT(onLabelsChanged(QStringList)));

    m_plot->setAttribute(Qt::WA_NoSystemBackground);
    m_plot->setAutoFillBackground(true);

    m_canvas->setPaintAttribute(QwtPlotCanvas::BackingStore, false);
    m_canvas->setLineWidth(1);
    m_canvas->setFrameStyle(QFrame::NoFrame);

    m_plot->setAxisScaleDraw(QwtPlot::yLeft, new SideScaleDraw()); //cleaned up by the plot
    m_plot->setAxisScaleDraw(QwtPlot::yRight, new BarScaleDraw()); //cleaned up by the plot
    m_plot->setAxisScaleDraw(QwtPlot::xBottom, new BarScaleDraw()); //cleaned up by the plot

    m_plot->setCanvas(m_canvas);

    m_barDataLeft->attach(m_plot);
    m_barDataLeft->setYAxis(QwtPlot::yLeft);

    m_barDataRight->attach(m_plot);
    m_barDataRight->setYAxis(QwtPlot::yRight);

    m_plot->setAutoReplot(true);
}

FftBarChart::~FftBarChart()
{
    delete m_canvas;
    delete m_plot;
}

bool FftBarChart::bottomLabels() const
{
    return m_bottomLabelsEnabled;
}

bool FftBarChart::legendEnabled() const
{
    return m_legendEnabled;
}

QColor FftBarChart::bgColor() const
{
    return m_bgColor;
}

QColor FftBarChart::borderColor() const
{
    return m_borderColor;
}

QColor FftBarChart::textColor() const
{
    return m_textColor;
}

QString FftBarChart::chartTitle() const
{
    return m_chartTitle;
}

void FftBarChart::paint(QPainter *t_painter)
{
    //painter->setRenderHints(QPainter::Antialiasing, true);
    m_plot->render(t_painter);
}

bool FftBarChart::logScaleLeftAxis() const
{
    return m_logScaleLeftAxis;
}

double FftBarChart::maxValueLeftAxis() const
{
    return m_maxValueLeftAxis;
}

double FftBarChart::minValueLeftAxis() const
{
    return m_minValueLeftAxis;
}

QColor FftBarChart::colorLeftAxis() const
{
    return m_colorLeftAxis;
}

QString FftBarChart::titleLeftAxis() const
{
    return m_plot->axisTitle(QwtPlot::yLeft).text();
}

bool FftBarChart::logScaleRightAxis() const
{
    return m_logScaleRightAxis;
}

double FftBarChart::maxValueRightAxis() const
{
    return m_maxValueRightAxis;
}

double FftBarChart::minValueRightAxis() const
{
    return m_minValueRightAxis;
}

QColor FftBarChart::colorRightAxis() const
{
    return m_colorRightAxis;
}

bool FftBarChart::rightAxisEnabled() const
{
    return m_plot->axisEnabled(QwtPlot::yRight);
}

QString FftBarChart::titleRightAxis() const
{
    return m_plot->axisTitle(QwtPlot::yLeft).text();
}

void FftBarChart::onExternValuesChanged()
{
    startUpdate();
}

void FftBarChart::onHeightChanged()
{
    if(contentsBoundingRect().height() > 0)
        m_plot->setFixedHeight(contentsBoundingRect().height());
    else
        m_plot->setFixedHeight(0);
}

void FftBarChart::onWidthChanged()
{
    if(contentsBoundingRect().width() > 0)
        m_plot->setFixedWidth(contentsBoundingRect().width());
    else
        m_plot->setFixedWidth(0);
}

void FftBarChart::setBgColor(const QColor &backgroundColor)
{
    if (m_bgColor != backgroundColor) {
        QPalette p = m_plot->palette();
        p.setColor(QPalette::Window, backgroundColor);
        m_canvas->setPalette(p);
        m_bgColor = backgroundColor;
        emit bgColorChanged(backgroundColor);
        startUpdate();
    }
}

void FftBarChart::setborderColor(const QColor &borderColor)
{
    if (m_borderColor != borderColor) {
        m_borderColor = borderColor;
        /// @todo Broken TBD
        emit borderColorChanged(borderColor);
        startUpdate();
    }
}

void FftBarChart::useBottomLabels(bool labelsEnabled)
{
    m_bottomLabelsEnabled=labelsEnabled;
    if(labelsEnabled) {
        m_plot->setAxisScaleDraw(QwtPlot::xBottom, new BarScaleDraw(Qt::Vertical, m_bottomLabels)); //cleaned up by the plot
        m_plot->setAxisMaxMajor(QwtPlot::xBottom, m_bottomLabels.count());
    }
    else {
        m_bottomLabels.clear();
        m_plot->setAxisScaleDraw(QwtPlot::xBottom, new BarScaleDraw()); //cleaned up by the plot
    }
}

void FftBarChart::setChartTitle(const QString &chartTitle)
{
    if (m_chartTitle != chartTitle) {
        m_chartTitle = chartTitle;
        m_plot->setTitle(chartTitle);
    }
}

void FftBarChart::setLegendEnabled(bool legendEnabled)
{
    if (legendEnabled!=m_legendEnabled) {
        if(legendEnabled) {
            QwtLegend *tmpLegend = new QwtLegend(); // cleaned up by the plot
            m_plot->insertLegend(tmpLegend);
        }
        else
            m_plot->insertLegend(nullptr);
    }
    m_legendEnabled=legendEnabled;
}

void FftBarChart::setTextColor(const QColor &textColor)
{
    if(textColor != m_textColor) {
        QPalette tmpPa;
        tmpPa.setColor(QPalette::Text, textColor);
        tmpPa.setColor(QPalette::WindowText, textColor);
        m_plot->setPalette(tmpPa);

        if(m_plot->legend())
            m_plot->legend()->setPalette(tmpPa);

        m_plot->axisWidget(QwtPlot::xBottom)->setPalette(tmpPa);

        BarScaleDraw *tmpScaleX=new BarScaleDraw(); //cleaned up by the plot
        tmpScaleX->setColor(textColor);

        ///todo check if this is necessary since the palette was set previously
        m_plot->setAxisScaleDraw(QwtPlot::xBottom, tmpScaleX);

        labelsChanged(m_bottomLabels);
        m_textColor = textColor;

        startUpdate();
    }
}

void FftBarChart::setLogScaleLeftAxis(bool useLogScale)
{
    if(useLogScale!=m_logScaleLeftAxis) {
        m_logScaleLeftAxis = useLogScale;
        if(useLogScale) {
            m_plot->setAxisScaleEngine(QwtPlot::yLeft, new QwtLogScaleEngine); //cleaned up by the plot
        }
        else {
            m_plot->setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine); //cleaned up by the plot
        }
        m_plot->setAxisScale(QwtPlot::yLeft, m_minValueLeftAxis, m_maxValueLeftAxis);
        m_barDataLeft->setBaseline(m_minValueLeftAxis/10);
        //calculate optimised scale min/max
        setMaxValueLeftAxis(m_maxValueLeftAxis);
        setMinValueLeftAxis(m_minValueLeftAxis);
    }
}

void FftBarChart::setMaxValueLeftAxis(double maxValue)
{
    double tmpScale=1;
    if(m_logScaleLeftAxis) {
        while(tmpScale<maxValue) {
            tmpScale=tmpScale*10;
        }
    }
    else {
        tmpScale=maxValue;
    }
    m_plot->setAxisScale(QwtPlot::yLeft, m_minValueLeftAxis, tmpScale);
    m_maxValueLeftAxis = maxValue;
}

void FftBarChart::setMinValueLeftAxis(double minValue)
{
    double tmpScale=1;
    if(m_logScaleLeftAxis) {
        while(tmpScale>minValue) {
            tmpScale=tmpScale/10;
        }
    }
    else {
        tmpScale=minValue;
    }
    m_plot->setAxisScale(QwtPlot::yLeft, tmpScale, m_maxValueLeftAxis);
    m_minValueLeftAxis = minValue;
}

void FftBarChart::setColorLeftAxis(const QColor &color)
{
    if (m_colorLeftAxis != color) {
        QPalette tmpPa;
        tmpPa.setColor(QPalette::Text, color);
        tmpPa.setColor(QPalette::WindowText, color);

        m_plot->axisWidget(QwtPlot::yLeft)->setPalette(tmpPa);
        m_colorLeftAxis = color;

        startUpdate();
    }
}

void FftBarChart::setTitleLeftAxis(const QString &title)
{
    m_plot->setAxisTitle(QwtPlot::yLeft, title);
}

void FftBarChart::setLogScaleRightAxis(bool useLogScale)
{
    if(useLogScale!=m_logScaleRightAxis) {
        m_logScaleRightAxis = useLogScale;
        if(useLogScale) {
            m_plot->setAxisScaleEngine(QwtPlot::yRight, new QwtLogScaleEngine); //cleaned up by the plot
        }
        else {
            m_plot->setAxisScaleEngine(QwtPlot::yRight, new QwtLinearScaleEngine); //cleaned up by the plot
        }
        m_plot->setAxisScale(QwtPlot::yRight, m_minValueRightAxis, m_maxValueRightAxis);
        m_barDataRight->setBaseline(m_minValueRightAxis/10);
        //calculate optimised scale min/max
        setMaxValueRightAxis(m_maxValueRightAxis);
        setMinValueRightAxis(m_minValueRightAxis);
    }
}

void FftBarChart::setMaxValueRightAxis(double maxValue)
{
    double tmpScale=1;
    if(m_logScaleRightAxis) {
        while(tmpScale<maxValue) {
            tmpScale=tmpScale*10;
        }
    }
    else {
        tmpScale=maxValue;
    }
    m_plot->setAxisScale(QwtPlot::yRight, m_minValueRightAxis, tmpScale);
    m_maxValueRightAxis = maxValue;
}

void FftBarChart::setMinValueRightAxis(double minValue)
{
    double tmpScale=1;
    if(m_logScaleRightAxis) {
        while(tmpScale>minValue) {
            tmpScale=tmpScale/10;
        }
    }
    else {
        tmpScale=minValue;
    }
    m_plot->setAxisScale(QwtPlot::yRight, tmpScale, m_maxValueRightAxis);
    m_minValueRightAxis = minValue;
}

void FftBarChart::setColorRightAxis(const QColor &color)
{
    if (m_colorRightAxis != color) {
        QPalette tmpPa;
        tmpPa.setColor(QPalette::Text, color);
        tmpPa.setColor(QPalette::WindowText, color);

        m_plot->axisWidget(QwtPlot::yRight)->setPalette(tmpPa);
        m_colorRightAxis = color;

        startUpdate();
    }
}

void FftBarChart::setTitleRightAxis(const QString &title)
{
    m_plot->setAxisTitle(QwtPlot::yRight, title);
}

void FftBarChart::setRightAxisEnabled(bool rightAxisEnabled)
{
    m_plot->enableAxis(QwtPlot::yRight, rightAxisEnabled);
}

void FftBarChart::updateBarsAndLegends()
{
    QVector<double> tmpSamples;
    const float tmpScaleFactor = m_maxValueLeftAxis/m_maxValueRightAxis;

    if(m_valuesLeftAxis.count()>0 && m_valuesLeftAxis.count() == m_valuesRightAxis.count()) {
        //m_valuesLeftAxis is a list of mixed real and imaginary numbers
        //and m_valuesRightAxis needs to be mudballed into the samples
        int tmpLeftBarCount = m_valuesLeftAxis.count();
        m_barDataLeft->clearData();
        for(int i=0; i<tmpLeftBarCount-1; i+=2) {
            m_barDataLeft->addData(m_colorLeftAxis, QString::number(i/2));
            m_barDataLeft->addData(m_colorRightAxis, QString(" "));
        }

        for(int i=0; i<tmpLeftBarCount-1; i+=2) {
            QVector2D tmpVectorA, tmpVectorB;

            tmpVectorA.setX(m_valuesLeftAxis.at(i));
            tmpVectorA.setY(m_valuesLeftAxis.at(i+1));

            tmpSamples.append(tmpVectorA.length());

            tmpVectorB.setX(m_valuesRightAxis.at(i));
            tmpVectorB.setY(m_valuesRightAxis.at(i+1));

            //this is bullshit, but due to management decisions it is required
            tmpSamples.append(tmpVectorB.length()*tmpScaleFactor);
        }

        if(m_legendEnabled)
            m_plot->insertLegend(new QwtLegend()); //cleaned up by the plot
        emit labelsChanged(m_barDataLeft->getTitles());
    }
    m_barDataLeft->setSamples(tmpSamples);
}

void FftBarChart::onLabelsChanged(const QStringList &labels)
{
    m_bottomLabels=labels;
    useBottomLabels(m_bottomLabelsEnabled);
}

void FftBarChart::onLeftValueChanged(const QVariant &leftValue)
{
    m_valuesLeftAxis = leftValue.value<QList<qreal>>();
    onExternValuesChanged();
}

void FftBarChart::onRightValueChanged(const QVariant &rightValue)
{
    m_valuesRightAxis = rightValue.value<QList<double>>();
    onExternValuesChanged();
}

void FftBarChart::onUpdateTimer()
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

void FftBarChart::startUpdate()
{
    m_updateTimer = TimerFactoryQt::createSingleShot(10);
    connect(m_updateTimer.get(), &TimerTemplateQt::sigExpired,
            this, &FftBarChart::onUpdateTimer);
    m_updateTimer->start();
}
