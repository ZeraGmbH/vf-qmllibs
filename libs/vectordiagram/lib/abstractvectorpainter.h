#ifndef ABSTRACTVECTORPAINTER_H
#define ABSTRACTVECTORPAINTER_H

#include <QPainter>

class AbstractVectorPainter
{
public:
    virtual void paint(QPainter *painter) = 0;
};

#endif // ABSTRACTVECTORPAINTER_H
