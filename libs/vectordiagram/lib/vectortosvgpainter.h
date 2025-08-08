#ifndef VECTORTOSVGPAINTER_H
#define VECTORTOSVGPAINTER_H

#include "vectorpaintcontroller.h"
#include <QString>
#include <QByteArray>
#include <QSvgGenerator>
#include <QPainter>

class VectorToSvgPainter
{
public:
    VectorToSvgPainter(int width, int height,
                       const QString &title = "", const QString &description = "");
    VectorPaintController *getVectorPainter();
    void paintToFile(const QString &fileName);
    QByteArray paintByteArray();
private:
    const int m_width;
    const int m_height;
    const QString m_title;
    const QString m_description;

    VectorPaintController m_vectorPainter;
    QPainter m_painter;
};

#endif // VECTORTOSVGPAINTER_H
