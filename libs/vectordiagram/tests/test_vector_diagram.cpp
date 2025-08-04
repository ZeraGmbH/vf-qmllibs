#include "test_vector_diagram.h"
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
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
    vectorPainter->setGridVisible(false);
    vectorPainter->setCircleVisible(false);
    svgPainter.paintToFile(dumpFile);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);

    dumped = svgPainter.paintByteArray(); // check byte array variant once
    ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::gridOnlySquare()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
    vectorPainter->setGridVisible(true);
    vectorPainter->setCircleVisible(false);
    svgPainter.paintToFile(dumpFile);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);

    dumped = svgPainter.paintByteArray(); // check byte array variant once
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
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
    vectorPainter->setGridVisible(true);
    vectorPainter->setCircleVisible(false);
    svgPainter.paintToFile(dumpFile);

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
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
    vectorPainter->setGridVisible(true);
    vectorPainter->setCircleVisible(false);
    svgPainter.paintToFile(dumpFile);

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
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
    vectorPainter->setGridVisible(true);
    vectorPainter->setGridColor(Qt::blue);
    vectorPainter->setCircleVisible(false);
    svgPainter.paintToFile(dumpFile);

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
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
    vectorPainter->setGridVisible(true);
    vectorPainter->setCircleVisible(true);
    vectorPainter->setMaxOvershootFactor(1.0);
    svgPainter.paintToFile(dumpFile);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);

    dumped = svgPainter.paintByteArray(); // check byte array variant once
    ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::gridAndCircleOvershoot()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
    vectorPainter->setGridVisible(true);
    vectorPainter->setCircleVisible(true);
    vectorPainter->setMaxOvershootFactor(2.0);
    svgPainter.paintToFile(dumpFile);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);

    dumped = svgPainter.paintByteArray(); // check byte array variant once
    ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram::gridAndCircleBlue()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
    vectorPainter->setGridVisible(true);
    vectorPainter->setCircleVisible(true);
    vectorPainter->setCircleColor(Qt::blue);
    svgPainter.paintToFile(dumpFile);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);

    dumped = svgPainter.paintByteArray(); // check byte array variant once
    ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

Q_DECLARE_METATYPE(VectorPainter::VectorType)



void test_vector_diagram::setSymmetricValues(VectorPainter *painter, double uValue, double iValue, double iAngle)
{
    int dark = 130;
    QVector<QColor> colors{QColor("red").darker(dark), QColor("yellow").darker(dark), QColor("blue").darker(dark),
                           QColor("red").lighter(), QColor("yellow").lighter(), QColor("blue").lighter()};

    constexpr double overload = 1.25;
    painter->setMaxOvershootFactor(overload);

    double uLen = uValue * M_SQRT2;
    painter->setNominalVoltage(uLen);

    double iLen = iValue * M_SQRT2;
    painter->setNominalCurrent(iLen);

    for (int i=0; i<VectorPainter::COUNT_PHASES; i++) {
        int uIdx = i;
        int iIdx = i + VectorPainter::COUNT_PHASES;
        painter->setVectorColor(uIdx, colors[uIdx]);
        painter->setVectorColor(iIdx, colors[iIdx]);

        painter->setVectorLabel(i, QString("UL%1").arg(i+1));
        painter->setVectorLabel(i+VectorPainter::COUNT_PHASES, QString("IL%1").arg(i+1));

        const double uPhi = gradToDeg(i*120);
        std::complex<double> uRawValue = std::polar<double>(uLen, uPhi);
        painter->setVector(i, QVector2D(uRawValue.real(), uRawValue.imag()));

        const double iPhi = uPhi + gradToDeg(iAngle);
        std::complex<double> iRawValue = std::polar<double>(iLen, iPhi);
        painter->setVector(i+VectorPainter::COUNT_PHASES, QVector2D(iRawValue.real(), iRawValue.imag()));
    }
}

double test_vector_diagram::gradToDeg(double angle)
{
    return 2*M_PI * angle/360;
}
