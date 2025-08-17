#include "test_vector_diagram.h"
#include "vectorpaintcalc.h"
#include "vectortosvgpainter.h"
#include <testvaluesetter.h>
#include <complex>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

QTEST_MAIN(test_vector_diagram)

void test_vector_diagram::initTestCase()
{
    QDir dir;
    dir.mkpath(TEST_SVG_FILE_PATH);
}

void test_vector_diagram::init()
{
    m_generator = std::make_unique<QSvgGenerator>();
    m_generator->setTitle(tr("Test SVG"));
    m_generator->setDescription("test_vector_diagram");
}

// We use huge numbers to avoid float/rounding problems and find scalabilty issues
constexpr int clipLenShort = 2000;
constexpr int clipLenLong = 3000;

void test_vector_diagram::noGridSquare()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(false);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(false);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::gridOnlySquare()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(false);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);

    dumped = svgPainter.paintByteArray(&vectorPainter); // check byte array variant once
    ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::gridOnlyRectangleWide()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenLong, clipLenShort);
    VectorPaintController vectorPainter;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(false);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::gridOnlyRectangleNarrow()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenLong);
    VectorPaintController vectorPainter;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(false);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::gridOnlyBlue()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenLong);
    VectorPaintController vectorPainter;
    QColor blue = Qt::blue;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossColor(blue);
    QCOMPARE(blue, vectorPainter.getVectorSettings()->m_layout.getCoordCrossColor());
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(false);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::gridAndCircleNoOvershoot()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::gridAndCircleOvershoot()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;
    const float over = 2.0;
    vectorPainter.getVectorSettings()->m_lengths.setMaxOvershootFactor(over);
    QCOMPARE(over, vectorPainter.getVectorSettings()->m_lengths.getMaxOvershootFactor());
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::gridAndCircleBlue()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;
    QColor blue = Qt::blue;
    vectorPainter.getVectorSettings()->m_layout.setCircleColor(blue);
    QCOMPARE(blue, vectorPainter.getVectorSettings()->m_layout.getCircleColor());
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::setCrossAndCircleLineWidth()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    const float width = 0.05;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossAndCircleLineWidth(width);
    QCOMPARE(width, vectorPainter.getVectorSettings()->m_layout.getCoordCrossAndCircleLineWidth());

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

void test_vector_diagram::setVectorLineWidth()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::setArrowHeight()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::setArrowWidthWide()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::setArrowWidthMix()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::setArrowWidthNarrow()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::setArrowWidthTooHigh()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::setArrowWidthTooLow()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::setFontSize()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::setDIN()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorStandard standard = VectorSettingsUser::VectorStandard::DIN;
    vectorPainter.getVectorSettings()->m_user.setVectorStandard(standard);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorStandard(), standard);

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

void test_vector_diagram::setDINUAngle()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorStandard standard = VectorSettingsUser::VectorStandard::DIN;
    vectorPainter.getVectorSettings()->m_user.setVectorStandard(standard);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorStandard(), standard);

    const float nomValue = 30;
    const float angle = 60;
    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    const double uPhi = degToRad(30);
    std::complex<double> u0RawValue = std::polar<double>(nomValue, uPhi);
    vectorPainter.setVector(0, QVector2D(u0RawValue.real(), u0RawValue.imag()));

    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::setIEC()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorStandard standard = VectorSettingsUser::VectorStandard::IEC;
    vectorPainter.getVectorSettings()->m_user.setVectorStandard(standard);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorStandard(), standard);

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

void test_vector_diagram::setANSI()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorStandard standard = VectorSettingsUser::VectorStandard::ANSI;
    vectorPainter.getVectorSettings()->m_user.setVectorStandard(standard);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorStandard(), standard);

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

void test_vector_diagram::setANSIUAngle()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorStandard standard = VectorSettingsUser::VectorStandard::ANSI;
    vectorPainter.getVectorSettings()->m_user.setVectorStandard(standard);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorStandard(), standard);

    const float nomValue = 30;
    const float angle = 60;
    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    const double uPhi = degToRad(30);
    std::complex<double> u0RawValue = std::polar<double>(nomValue, uPhi);
    vectorPainter.setVector(0, QVector2D(u0RawValue.real(), u0RawValue.imag()));

    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::setStar()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorType type = VectorSettingsUser::VectorType::STAR;
    vectorPainter.getVectorSettings()->m_user.setVectorType(type);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorType(), type);

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

void test_vector_diagram::setStarNoValues()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_user.setVectorType(VectorSettingsUser::VectorType::STAR);

    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::setTriangle()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorType type = VectorSettingsUser::VectorType::TRIANGLE;
    vectorPainter.getVectorSettings()->m_user.setVectorType(type);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorType(), type);

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

void test_vector_diagram::setTriangleNoCurrent()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_user.setVectorType(VectorSettingsUser::VectorType::TRIANGLE);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, 0, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::set3Wire()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 0;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorType type = VectorSettingsUser::VectorType::THREE_PHASE;
    vectorPainter.getVectorSettings()->m_user.setVectorType(type);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorType(), type);

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

void test_vector_diagram::setNominalMode()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float uNom = 230;
    const float iNom = 10;
    const float angle = -15;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::setMaximumMode()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float uNom = 230;
    const float iNom = 10;
    const float angle = -15;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::setMaximumTwice()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float uNom = 230;
    const float iNom = 10;
    const float angle = -15;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::setVectorStyleZenux0()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 0.0;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsLayout::VectorStyle width = VectorSettingsLayout::VectorStyle::ZENUX;
    vectorPainter.getVectorSettings()->m_layout.setVectorStyle(width);
    QCOMPARE(vectorPainter.getVectorSettings()->m_layout.getVectorStyle(), width);

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

void test_vector_diagram::setVectorStyleZenux30()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30.0;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsLayout::VectorStyle width = VectorSettingsLayout::VectorStyle::ZENUX;
    vectorPainter.getVectorSettings()->m_layout.setVectorStyle(width);
    QCOMPARE(vectorPainter.getVectorSettings()->m_layout.getVectorStyle(), width);

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

void test_vector_diagram::setVectorStyleWebSam0()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 0.0;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsLayout::VectorStyle width = VectorSettingsLayout::VectorStyle::WEBSAM;
    vectorPainter.getVectorSettings()->m_layout.setVectorStyle(width);
    QCOMPARE(vectorPainter.getVectorSettings()->m_layout.getVectorStyle(), width);

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

void test_vector_diagram::setVectorStyleWebSam30()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    VectorSettingsLayout::VectorStyle width = VectorSettingsLayout::VectorStyle::WEBSAM;
    vectorPainter.getVectorSettings()->m_layout.setVectorStyle(width);
    QCOMPARE(vectorPainter.getVectorSettings()->m_layout.getVectorStyle(), width);

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

void test_vector_diagram::starVectorsNoOvershoot()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float uNom = 230;
    const float iNom = 10;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;

    TestValueSetter::setSymmetricValues(&vectorPainter, uNom, iNom, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::starVectorsNoOvershootSmall()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float uNom = 230;
    const float iNom = 10;
    const float angle = 30;
    VectorToSvgPainter svgPainter(50, 50);
    VectorPaintController vectorPainter;

    TestValueSetter::setSymmetricValues(&vectorPainter, uNom, iNom, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::starVectorsIgnoreLessThanMin()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float uMin = 23;
    const float iMin = 1;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::vectorLabelsTooLong_data()
{
    QTest::addColumn<float>("overshoot");
    QVector<float> overshoots{1.1, 1.2, 1.3, 1.4, 1.5};
    for (float overshoot : overshoots) {
        const QString overshootLabel = QString("overshoot-%1").arg(overshoot);
        const QString rowName = QString("%1").arg(overshootLabel);
        QTest::newRow(rowName.toUtf8()) << overshoot;
    }
}

void test_vector_diagram::vectorLabelsTooLong()
{
    QFETCH(float, overshoot);
    const QString fileBase = QString(QTest::currentTestFunction()) + QTest::currentDataTag() + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nom = 1;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

void test_vector_diagram::vectorLabelsTooShort_data()
{
    QTest::addColumn<float>("undershoot");
    QVector<float> undershoots{0.6, 0.5, 0.4, 0.3, 0.2, 0.1};
    for (float undershoot : undershoots) {
        const QString undershootLabel = QString("undershoot-%1").arg(undershoot);
        const QString rowName = QString("%1").arg(undershootLabel);
        QTest::newRow(rowName.toUtf8()) << undershoot;
    }
}

void test_vector_diagram::vectorLabelsTooShort()
{
    QFETCH(float, undershoot);
    const QString fileBase = QString(QTest::currentTestFunction()) + QTest::currentDataTag() + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float nom = 1;
    const float angle = 15;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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
