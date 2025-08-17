#include "test_vector_label_font_size.h"
#include "vectortosvgpainter.h"
#include <testvaluesetter.h>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

QTEST_MAIN(test_vector_label_font_size)

constexpr int clipLen = 2000;

void test_vector_label_font_size::setFontSize()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float fontSize = 0.06;
    vectorPainter.getVectorSettings()->m_layout.setLabelFontSize(fontSize);
    QCOMPARE(vectorPainter.getVectorSettings()->m_layout.getLabelFontSize(), fontSize);

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

void test_vector_label_font_size::setFontTooHigh()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float fontSize = 10000;
    vectorPainter.getVectorSettings()->m_layout.setLabelFontSize(fontSize);

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

void test_vector_label_font_size::setFontTooLow()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float fontSize = -10000;
    vectorPainter.getVectorSettings()->m_layout.setLabelFontSize(fontSize);

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
