#ifndef TEST_PRIMITIVE_PAINTER_H
#define TEST_PRIMITIVE_PAINTER_H

#include "vectorsettings.h"
#include <QObject>
#include <QSvgGenerator>

class test_primitive_painter : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void init();

    void initialTestPrimitivePainterStar();
    void variationAngleOffsetRotationDir_data();
    void variationAngleOffsetRotationDir();

    void initialTestPrimitivePainterTriangle();

    void initialTestPrimitivePainterLabel();
private:
    std::unique_ptr<QSvgGenerator> m_generator;
    VectorSettings m_geomSettings;
};

#endif // TEST_PRIMITIVE_PAINTER_H
