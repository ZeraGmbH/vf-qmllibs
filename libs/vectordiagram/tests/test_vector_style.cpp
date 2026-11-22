#include "test_vector_style.h"
#include "vectorpaintcontroller.h"
#include "vectortosvgpainter.h"
#include <testvaluesetter.h>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

constexpr int clipLen = 2000;

QTEST_MAIN(test_vector_style)

void test_vector_style::setVectorStyleZenux0()
{
    const float nomValue = 30;
    const float angle = 0.0;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    VectorSettingsLayout::VectorStyle width = VectorSettingsLayout::VectorStyle::ZENUX;
    vectorPainter.getVectorSettings()->m_layout.setVectorStyle(width);
    QCOMPARE(vectorPainter.getVectorSettings()->m_layout.getVectorStyle(), width);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_style::setVectorStyleZenux30()
{
    const float nomValue = 30;
    const float angle = 30.0;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    VectorSettingsLayout::VectorStyle width = VectorSettingsLayout::VectorStyle::ZENUX;
    vectorPainter.getVectorSettings()->m_layout.setVectorStyle(width);
    QCOMPARE(vectorPainter.getVectorSettings()->m_layout.getVectorStyle(), width);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_style::setVectorStyleWebSam0()
{
    const float nomValue = 30;
    const float angle = 0.0;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    VectorSettingsLayout::VectorStyle width = VectorSettingsLayout::VectorStyle::WEBSAM;
    vectorPainter.getVectorSettings()->m_layout.setVectorStyle(width);
    QCOMPARE(vectorPainter.getVectorSettings()->m_layout.getVectorStyle(), width);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_style::setVectorStyleWebSam30()
{
    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    VectorSettingsLayout::VectorStyle width = VectorSettingsLayout::VectorStyle::WEBSAM;
    vectorPainter.getVectorSettings()->m_layout.setVectorStyle(width);
    QCOMPARE(vectorPainter.getVectorSettings()->m_layout.getVectorStyle(), width);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}
