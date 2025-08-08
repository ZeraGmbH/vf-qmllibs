#include "vectortosvgpainter.h"
#include <QBuffer>

VectorToSvgPainter::VectorToSvgPainter(int width, int height,
                                       const QString &title, const QString &description) :
    m_width(width),
    m_height(height),
    m_title(title),
    m_description(description)
{
}

VectorPaintController *VectorToSvgPainter::getVectorPainter()
{
    return &m_vectorPainter;
}

void VectorToSvgPainter::paintToFile(const QString &fileName)
{
    QSvgGenerator svgGenerator;
    svgGenerator.setSize(QSize(m_width, m_height));
    svgGenerator.setViewBox(QRect(0, 0, m_width, m_height));
    svgGenerator.setTitle(m_title);
    svgGenerator.setDescription(m_description);
    svgGenerator.setFileName(fileName);

    m_painter.begin(&svgGenerator);
    m_vectorPainter.paint(&m_painter);
    m_painter.end();
}

QByteArray VectorToSvgPainter::paintByteArray()
{
    QByteArray svgGenerated;
    QBuffer buff(&svgGenerated);

    QSvgGenerator svgGenerator;
    svgGenerator.setSize(QSize(m_width, m_height));
    svgGenerator.setViewBox(QRect(0, 0, m_width, m_height));
    svgGenerator.setTitle(m_title);
    svgGenerator.setDescription(m_description);
    svgGenerator.setOutputDevice(&buff);

    m_painter.begin(&svgGenerator);
    m_vectorPainter.paint(&m_painter);
    m_painter.end();
    return svgGenerated;
}
