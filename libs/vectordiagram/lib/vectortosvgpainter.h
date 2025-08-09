#ifndef VECTORTOSVGPAINTER_H
#define VECTORTOSVGPAINTER_H

#include "abstractvectorpainter.h"
#include <QString>
#include <QByteArray>
#include <QSvgGenerator>
#include <QPainter>

class VectorToSvgPainter
{
public:
    VectorToSvgPainter(int width, int height,
                       const QString &title = "", const QString &description = "");
    void paintToFile(const QString &fileName, AbstractVectorPainter* abstractPainter);
    QByteArray paintByteArray(AbstractVectorPainter *abstractPainter);
private:
    const int m_width;
    const int m_height;
    const QString m_title;
    const QString m_description;

    QPainter m_painter;
};

#endif // VECTORTOSVGPAINTER_H
