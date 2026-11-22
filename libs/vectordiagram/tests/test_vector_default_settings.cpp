#include "test_vector_default_settings.h"
#include "vectortosvgpainter.h"
#include <testvaluesetter.h>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

QTEST_MAIN(test_vector_default_settings)

constexpr int clipLen = 2000;

void test_vector_default_settings::starVectorsNoOvershoot()
{
    const float uNom = 230;
    const float iNom = 10;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    TestValueSetter::setSymmetricValues(&vectorPainter, uNom, iNom, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_default_settings::starVectorsNoOvershootSmall()
{
    const float uNom = 230;
    const float iNom = 10;
    const float angle = 30;
    VectorToSvgPainter svgPainter(50, 50);
    VectorPaintController vectorPainter;

    TestValueSetter::setSymmetricValues(&vectorPainter, uNom, iNom, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

