#include "test_vector_line_width.h"
#include "vectortosvgpainter.h"
#include <testvaluesetter.h>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

QTEST_MAIN(test_vector_line_width)

constexpr int clipLen = 2000;

void test_vector_line_width::setVectorLineWidth()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float width = 0.02;
    vectorPainter.getVectorSettings()->m_layout.setVectorLineWidthU(width*2);
    QCOMPARE(width*2, vectorPainter.getVectorSettings()->m_layout.getVectorLineWidthU());
    vectorPainter.getVectorSettings()->m_layout.setVectorLineWidthI(width);
    QCOMPARE(width, vectorPainter.getVectorSettings()->m_layout.getVectorLineWidthI());

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_line_width::setVectorLineWidthTooHigh()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float width = 10000;
    vectorPainter.getVectorSettings()->m_layout.setVectorLineWidthU(width*2);
    vectorPainter.getVectorSettings()->m_layout.setVectorLineWidthI(width);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_line_width::setVectorLineWidthTooLow()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float width = -10000;
    vectorPainter.getVectorSettings()->m_layout.setVectorLineWidthU(width*2);
    vectorPainter.getVectorSettings()->m_layout.setVectorLineWidthI(width);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}
