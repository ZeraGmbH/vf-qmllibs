#include "test_primitive_painter.h"
#include "testprimitivepainterstar.h"
#include "testprimitivepaintertriangle.h"
#include "testprimitivepainterlabel.h"
#include "vectorpaintcalc.h"
#include "vectortosvgpainter.h"
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

QTEST_MAIN(test_primitive_painter)

void test_primitive_painter::initTestCase()
{
    QDir dir;
    dir.mkpath(TEST_SVG_FILE_PATH);
}

void test_primitive_painter::init()
{
    m_generator = std::make_unique<QSvgGenerator>();
    m_generator->setTitle(tr("Test SVG"));
    m_generator->setDescription("test_primitive_painter");
}

constexpr int clipLen = 3000;

void test_primitive_painter::initialTestPrimitivePainterStar()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLen, clipLen);
    TestPrimitivePainterStar primPainter;
    svgPainter.paintToFile(dumpFile, &primPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_primitive_painter::variationAngleOffsetRotationDir_data()
{
    QTest::addColumn<float>("angleOffset");
    QTest::addColumn<RotationDirection>("rotationDir");
    const QVector<float> angleOffsets { 0, 90, 180, 270 };
    const QVector<RotationDirection> rotationDirs {
        RotationDirection::Mathematical,
        RotationDirection::Clockwise };
    for (float angleOffset : angleOffsets) {
        for (auto rotationDir : rotationDirs) {
            const QString angleOffsetLabel = QString("offset-%1").arg(angleOffset);
            const QString rotationDirLabel = QString("rotatdir-%1").
                                              arg(rotationDir == RotationDirection::Mathematical ? "math" : "clock");
            const QString rowName = QString("%1_%2").arg(angleOffsetLabel, rotationDirLabel);
            QTest::newRow(rowName.toUtf8()) << angleOffset << rotationDir;
        }
    }
}

void test_primitive_painter::variationAngleOffsetRotationDir()
{
    QFETCH(float, angleOffset);
    QFETCH(RotationDirection, rotationDir);
    const QString fileBase = QString(QTest::currentTestFunction()) + QTest::currentDataTag() + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    TestPrimitivePainterStar primPainter;
    primPainter.m_vectorSettings.m_angles.setOffsetAngle(degToRad(angleOffset));
    primPainter.m_vectorSettings.m_angles.setRotationDirection(rotationDir);

    VectorToSvgPainter svgPainter(clipLen, clipLen);
    svgPainter.paintToFile(dumpFile, &primPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_primitive_painter::initialTestPrimitivePainterTriangle()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLen, clipLen);
    TestPrimitivePainterTriangle primPainter;
    svgPainter.paintToFile(dumpFile, &primPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_primitive_painter::initialTestPrimitivePainterLabel()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(500, 500);
    TestPrimitivePainterLabel primPainter;
    svgPainter.paintToFile(dumpFile, &primPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}
