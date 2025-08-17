#ifndef TEST_PRIMITIVE_PAINTER_H
#define TEST_PRIMITIVE_PAINTER_H

#include <QObject>

class test_primitive_painter : public QObject
{
    Q_OBJECT
private slots:
    void initialTestPrimitivePainterStar();
    void variationAngleOffsetRotationDir_data();
    void variationAngleOffsetRotationDir();

    void initialTestPrimitivePainterTriangle();

    void initialTestPrimitivePainterLabel();
};

#endif // TEST_PRIMITIVE_PAINTER_H
