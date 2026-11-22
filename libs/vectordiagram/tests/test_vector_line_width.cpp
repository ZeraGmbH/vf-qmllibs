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

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_line_width::setVectorLineWidthTooHigh()
{
    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float width = 10000;
    vectorPainter.getVectorSettings()->m_layout.setVectorLineWidthU(width*2);
    vectorPainter.getVectorSettings()->m_layout.setVectorLineWidthI(width);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_line_width::setVectorLineWidthTooLow()
{
    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    const float width = -10000;
    vectorPainter.getVectorSettings()->m_layout.setVectorLineWidthU(width*2);
    vectorPainter.getVectorSettings()->m_layout.setVectorLineWidthI(width);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}
