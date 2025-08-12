#include "test_vector_diagram.h"
#include "vectorpaintcalc.h"
#include "vectortosvgpainter.h"
#include <complex>
#include <xmldocumentcompare.h>
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
    XmlDocumentCompare compare;
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
    XmlDocumentCompare compare;
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
    XmlDocumentCompare compare;
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
    XmlDocumentCompare compare;
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
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossColor(Qt::blue);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(false);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(true);
    vectorPainter.getVectorSettings()->m_lengths.setMaxOvershootFactor(1.0);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(true);
    vectorPainter.getVectorSettings()->m_lengths.setMaxOvershootFactor(2.0);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleColor(Qt::blue);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(nomValue);
    // two variations...
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(nomValue*2.0);
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossAndCircleLineWidthRel(0.05);

    setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(nomValue);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(nomValue);

    vectorPainter.getVectorSettings()->m_layout.setVectorLineWidthRel(0.02);

    setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(nomValue);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(nomValue);

    vectorPainter.getVectorSettings()->m_layout.setArrowHeightRel(0.1);

    setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(nomValue);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(nomValue);

    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDeg(45);

    setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(nomValue);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(nomValue);

    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDeg(12);

    setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(nomValue);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(nomValue);

    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDeg(180);

    setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(nomValue);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(nomValue);

    vectorPainter.getVectorSettings()->m_layout.setArrowSpreadAngleDeg(0);

    setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(nomValue);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(nomValue);

    const float fontSize = 0.06;
    vectorPainter.getVectorSettings()->m_layout.setLabelFontSize(fontSize);
    QCOMPARE(vectorPainter.getVectorSettings()->m_layout.getLabelFontSize(), fontSize);

    setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(true);
    vectorPainter.getVectorSettings()->m_lengths.setMaxOvershootFactor(1.0);

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(uNom);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(iNom);
    setSymmetricValues(&vectorPainter, uNom, iNom, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
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
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(true);
    vectorPainter.getVectorSettings()->m_lengths.setMaxOvershootFactor(1.0);

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(uNom);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(iNom);
    setSymmetricValues(&vectorPainter, uNom, iNom, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::starVectorsIgnoreLessThanMin()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    const float uNom = 230;
    const float uMin = 23;
    const float iNom = 10;
    const float iMin = 1;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPaintController vectorPainter;
    vectorPainter.getVectorSettings()->m_layout.setCoordCrossVisible(true);
    vectorPainter.getVectorSettings()->m_layout.setCircleVisible(true);
    vectorPainter.getVectorSettings()->m_lengths.setMaxOvershootFactor(1.0);

    vectorPainter.getVectorSettings()->m_lengths.setNomVoltage(uNom);
    vectorPainter.getVectorSettings()->m_lengths.setMinVoltage(uMin);
    vectorPainter.getVectorSettings()->m_lengths.setNomCurrent(iNom);
    vectorPainter.getVectorSettings()->m_lengths.setMinCurrent(iMin);
    setSymmetricValues(&vectorPainter, uMin*0.99, iMin*0.99, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}


Q_DECLARE_METATYPE(VectorPaintController::VectorType)



void test_vector_diagram::setSymmetricValues(VectorPaintController *painter, double uValue, double iValue, double iAngle)
{
    int dark = 130;
    QVector<QColor> colors{QColor("red").darker(dark), QColor("yellow"), QColor("blue").darker(dark),
                           QColor("red").lighter(), QColor("yellow").lighter(160), QColor("blue").lighter()};

    for (int i=0; i<VectorSettingsStatic::COUNT_PHASES; i++) {
        int uIdx = i;
        int iIdx = i + VectorSettingsStatic::COUNT_PHASES;
        painter->setVectorColor(uIdx, colors[uIdx]);
        painter->setVectorColor(iIdx, colors[iIdx]);

        painter->setVectorLabel(i, QString("UL%1").arg(i+1));
        painter->setVectorLabel(i+VectorSettingsStatic::COUNT_PHASES, QString("IL%1").arg(i+1));

        const double uPhi = degToRad(i*120);
        std::complex<double> uRawValue = std::polar<double>(uValue, uPhi);
        painter->setVector(i, QVector2D(uRawValue.real(), uRawValue.imag()));

        const double iPhi = uPhi + degToRad(iAngle);
        std::complex<double> iRawValue = std::polar<double>(iValue, iPhi);
        painter->setVector(i+VectorSettingsStatic::COUNT_PHASES, QVector2D(iRawValue.real(), iRawValue.imag()));
    }
}
