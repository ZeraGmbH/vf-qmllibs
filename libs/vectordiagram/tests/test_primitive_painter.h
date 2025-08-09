#ifndef TEST_PRIMITIVE_PAINTER_H
#define TEST_PRIMITIVE_PAINTER_H

#include "vectorsettingsgeometry.h"
#include <QObject>
#include <QSvgGenerator>

class test_primitive_painter : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void init();
    void twoVector_data();
    void twoVector();
private:
    double gradToDeg(double angle);
    std::unique_ptr<QSvgGenerator> m_generator;
    VectorSettingsGeometry m_geomSettings;
};

#endif // TEST_PRIMITIVE_PAINTER_H
