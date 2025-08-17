#include "test_vector_nominal_maximum.h"
#include "vectorpaintcontroller.h"
#include "vectortosvgpainter.h"
#include <testvaluesetter.h>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

constexpr int clipLen = 2000;

QTEST_MAIN(test_vector_nominal_maximum)

void test_vector_nominal_maximum::setNominalMode()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float uNom = 230;
    const float iNom = 10;
    const float angle = -15;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(uNom);
    QCOMPARE(uNom, vectorPainter.getVectorSettings()->m_lengths.getNomVoltage());
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(iNom);
    QCOMPARE(iNom, vectorPainter.getVectorSettings()->m_lengths.getNomCurrent());

    vectorPainter.getVectorSettings()->m_lengths.setNominalSelection(VectorSettingsLengths::VectorNominals::NOMINAL);
    QCOMPARE(VectorSettingsLengths::VectorNominals::NOMINAL, vectorPainter.getVectorSettings()->m_lengths.getNominalSelection());

    TestValueSetter::setSymmetricValues(&vectorPainter, uNom*2/3, iNom*1/3, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);

}

void test_vector_nominal_maximum::setMaximumMode()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float uNom = 230;
    const float iNom = 10;
    const float angle = -15;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;
    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(uNom);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(iNom);

    vectorPainter.getVectorSettings()->m_lengths.setNominalSelection(VectorSettingsLengths::VectorNominals::MAXIMUM);
    QCOMPARE(VectorSettingsLengths::VectorNominals::MAXIMUM, vectorPainter.getVectorSettings()->m_lengths.getNominalSelection());

    TestValueSetter::setSymmetricValues(&vectorPainter, uNom*2/3, iNom*1/3, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_nominal_maximum::setMaximumTwice()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float uNom = 230;
    const float iNom = 10;
    const float angle = -15;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;
    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(uNom);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(iNom);

    vectorPainter.getVectorSettings()->m_lengths.setNominalSelection(VectorSettingsLengths::VectorNominals::MAXIMUM);
    TestValueSetter::setSymmetricValues(&vectorPainter, uNom, iNom, angle); // start large
    svgPainter.paintToFile(dumpFile, &vectorPainter);
    TestValueSetter::setSymmetricValues(&vectorPainter, uNom*2/3, iNom*1/3, angle); // continue small
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}
