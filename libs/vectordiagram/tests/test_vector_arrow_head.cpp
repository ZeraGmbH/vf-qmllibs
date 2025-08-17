#include "test_vector_arrow_head.h"
#include "vectorpaintcontroller.h"
#include "vectortosvgpainter.h"
#include <testvaluesetter.h>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

constexpr int clipLen = 2000;

QTEST_MAIN(test_vector_arrow_head)

void test_vector_arrow_head::setArrowHeight()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float height = 0.1;
    vectorPainter.getVectorSettings()->m_layout.setArrowHeightU(height*2);
    QCOMPARE(height*2, vectorPainter.getVectorSettings()->m_layout.getArrowHeightU());
    vectorPainter.getVectorSettings()->m_layout.setArrowHeightI(height);
    QCOMPARE(height, vectorPainter.getVectorSettings()->m_layout.getArrowHeightI());

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

void test_vector_arrow_head::setArrowHeightTooHigh()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float height = 10000;
    vectorPainter.getVectorSettings()->m_layout.setArrowHeightU(height*2);
    vectorPainter.getVectorSettings()->m_layout.setArrowHeightI(height);

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

void test_vector_arrow_head::setArrowHeightTooLow()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float height = -10000;
    vectorPainter.getVectorSettings()->m_layout.setArrowHeightU(height*2);
    vectorPainter.getVectorSettings()->m_layout.setArrowHeightI(height);

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

void test_vector_arrow_head::setArrowWidthWide()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float angleArrow = 45;
    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDegU(angleArrow);
    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDegI(angleArrow);

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

void test_vector_arrow_head::setArrowWidthMix()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float angleArrowU = 45;
    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDegU(angleArrowU);
    QCOMPARE(angleArrowU, vectorPainter.getVectorSettings()->m_layout.getArrowSpreadAngleDegU());
    const float angleArrowI = 10;
    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDegI(angleArrowI);
    QCOMPARE(angleArrowI, vectorPainter.getVectorSettings()->m_layout.getArrowSpreadAngleDegI());

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

void test_vector_arrow_head::setArrowWidthNarrow()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDegU(12);
    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDegI(12);

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

void test_vector_arrow_head::setArrowWidthTooHigh()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDegU(180);
    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDegI(180);

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

void test_vector_arrow_head::setArrowWidthTooLow()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDegU(0);
    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDegI(0);

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
