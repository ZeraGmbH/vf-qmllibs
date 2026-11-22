#include "test_coord_cross_and_circle.h"
#include "vectorpaintcontroller.h"
#include "vectortosvgpainter.h"
#include <testvaluesetter.h>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

constexpr int clipLenShort = 2000;
constexpr int clipLenLong = 3000;

QTEST_MAIN(test_coord_cross_and_circle)

void test_coord_cross_and_circle::noGridSquare()
{
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(false);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(false);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_coord_cross_and_circle::coordCrossOnlySquare()
{
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(false);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_coord_cross_and_circle::coordCrossOnlyRectangleWide()
{
    VectorToSvgPainter svgPainter(clipLenLong, clipLenShort);
    VectorPaintController vectorPainter;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(false);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_coord_cross_and_circle::coordCrossOnlyRectangleNarrow()
{
    VectorToSvgPainter svgPainter(clipLenShort, clipLenLong);
    VectorPaintController vectorPainter;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(false);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_coord_cross_and_circle::coordCrossOnlyBlue()
{
    VectorToSvgPainter svgPainter(clipLenShort, clipLenLong);
    VectorPaintController vectorPainter;
    QColor blue = Qt::blue;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossColor(blue);
    QCOMPARE(blue, vectorPainter.getVectorSettings()->m_layout.getCoordCrossColor());
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(false);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_coord_cross_and_circle::coordCrossAndCircleNoOvershoot()
{
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_coord_cross_and_circle::coordCrossAndCircleOvershoot()
{
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;
    const float over = 2.0;
    vectorPainter.getVectorSettings()->m_lengths.setMaxOvershootFactor(over);
    QCOMPARE(over, vectorPainter.getVectorSettings()->m_lengths.getMaxOvershootFactor());

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_coord_cross_and_circle::coordCrossAndCircleBlue()
{
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;
    QColor blue = Qt::blue;
    vectorPainter.getVectorSettings()->m_layout.setCircleColor(blue);
    QCOMPARE(blue, vectorPainter.getVectorSettings()->m_layout.getCircleColor());

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_coord_cross_and_circle::coordCrossAndCircleLineWidth()
{
    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    const float width = 0.05;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossAndCircleLineWidth(width);
    QCOMPARE(width, vectorPainter.getVectorSettings()->m_layout.getCoordCrossAndCircleLineWidth());

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}
