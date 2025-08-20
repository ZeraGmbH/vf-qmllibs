#include "test_vector_calc.h"
#include "vectorpaintcalc.h"
#include <QTest>

QTEST_MAIN(test_vector_calc)

void test_vector_calc::deg0()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(0)) - degToRad(0));
    QVERIFY(diff < 1e-6);
}

void test_vector_calc::deg359_999()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(359.999)) - degToRad(359.999));
    QVERIFY(diff < 1e-6);
}

void test_vector_calc::deg360()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(360)) - degToRad(0));
    QVERIFY(diff < 1e-6);
}

void test_vector_calc::deg360_111()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(360.111)) - degToRad(0.111));
    QVERIFY(diff < 1e-6);
}

void test_vector_calc::deg719()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(719)) - degToRad(359));
    QVERIFY(diff < 1e-6);
}

void test_vector_calc::deg720()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(720)) - degToRad(0));
    QVERIFY(diff < 1e-6);
}

void test_vector_calc::deg721()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(721)) - degToRad(1));
    QVERIFY(diff < 1e-6);
}

void test_vector_calc::deg_1()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(-1)) - degToRad(359));
    QVERIFY(diff < 1e-6);
}

void test_vector_calc::deg_359()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(-359)) - degToRad(1));
    QVERIFY(diff < 1e-6);
}

void test_vector_calc::deg_360()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(-360)) - degToRad(0));
    QVERIFY(diff < 1e-6);
}

void test_vector_calc::deg_361()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(-361)) - degToRad(359));
    QVERIFY(diff < 1e-6);
}

void test_vector_calc::deg_719()
{
    float diff = fabs(VectorPaintCalc::normalizeAngle(degToRad(-719)) - degToRad(1));
    QVERIFY(diff < 1e-6);
}
