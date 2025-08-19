#ifndef PIXVECTORSHOWN_H
#define PIXVECTORSHOWN_H

#include <QVector2D>
#include <QVector>

struct PixVectorShown {
    QVector2D wantedPixVectorLabel;
    bool shown;
};
typedef QVector<PixVectorShown> PixVectorsShown;

#endif // PIXVECTORSHOWN_H
