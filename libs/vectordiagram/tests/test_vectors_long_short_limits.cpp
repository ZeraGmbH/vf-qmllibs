#include "test_vectors_long_short_limits.h"
#include "vectorpaintcontroller.h"
#include "vectortosvgpainter.h"
#include <testvaluesetter.h>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

constexpr int clipLen = 2000;

QTEST_MAIN(test_vectors_long_short_limits)

void test_vectors_long_short_limits::starVectorsIgnoreLessThanMin()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float uMin = 23;
    const float iMin = 1;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_lengths.setMinVoltage(uMin);
    QCOMPARE(uMin, vectorPainter.getVectorSettings()->m_lengths.getMinVoltage());
    vectorPainter.getVectorSettings()->m_lengths.setMinCurrent(iMin);
    QCOMPARE(iMin, vectorPainter.getVectorSettings()->m_lengths.getMinCurrent());

    TestValueSetter::setSymmetricValues(&vectorPainter, uMin*0.99, iMin*0.99, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vectors_long_short_limits::vectorLabelsTooLong_data()
{
    QTest::addColumn<float>("overshoot");
    QVector<float> overshoots{1.1, 1.2, 1.3, 1.4, 1.5};
    for (float overshoot : overshoots) {
        const QString overshootLabel = QString("overshoot-%1").arg(overshoot);
        const QString rowName = QString("%1").arg(overshootLabel);
        QTest::newRow(rowName.toUtf8()) << overshoot;
    }
}

void test_vectors_long_short_limits::vectorLabelsTooLong()
{
    QFETCH(float, overshoot);
    const QString fileBase = QString(QTest::currentTestFunction()) + QTest::currentDataTag() + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nom = 1;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;
    TestValueSetter::setNominalUI(vectorPainter, nom);

    TestValueSetter::setSymmetricValues(&vectorPainter, nom*overshoot, nom*overshoot, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vectors_long_short_limits::vectorLabelsTooShort_data()
{
    QTest::addColumn<float>("undershoot");
    QVector<float> undershoots{0.6, 0.5, 0.4, 0.3, 0.2, 0.1};
    for (float undershoot : undershoots) {
        const QString undershootLabel = QString("undershoot-%1").arg(undershoot);
        const QString rowName = QString("%1").arg(undershootLabel);
        QTest::newRow(rowName.toUtf8()) << undershoot;
    }
}

void test_vectors_long_short_limits::vectorLabelsTooShort()
{
    QFETCH(float, undershoot);
    const QString fileBase = QString(QTest::currentTestFunction()) + QTest::currentDataTag() + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nom = 1;
    const float angle = 15;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;
    TestValueSetter::setNominalUI(vectorPainter, nom);

    TestValueSetter::setSymmetricValues(&vectorPainter, nom*undershoot, nom*undershoot, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}
