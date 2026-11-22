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

constexpr int clipLen = 3000;

void test_primitive_painter::initialTestPrimitivePainterStar()
{
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    TestPrimitivePainterStar primPainter;

    QString dumped = svgPainter.paintByteArray(&primPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
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

    TestPrimitivePainterStar primPainter;
    primPainter.m_vectorSettings.m_angles.setOffsetAngle(degToRad(angleOffset));
    primPainter.m_vectorSettings.m_angles.setRotationDirection(rotationDir);

    VectorToSvgPainter svgPainter(clipLen, clipLen);

    QString dumped = svgPainter.paintByteArray(&primPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + QTest::currentDataTag() + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_primitive_painter::initialTestPrimitivePainterTriangle()
{
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    TestPrimitivePainterTriangle primPainter;

    QString dumped = svgPainter.paintByteArray(&primPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_primitive_painter::initialTestPrimitivePainterLabel()
{
    VectorToSvgPainter svgPainter(500, 500);
    TestPrimitivePainterLabel primPainter;

    QString dumped = svgPainter.paintByteArray(&primPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}
