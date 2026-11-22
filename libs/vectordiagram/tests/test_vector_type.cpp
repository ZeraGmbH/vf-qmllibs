#include "test_vector_type.h"
#include "vectorpaintcontroller.h"
#include "vectortosvgpainter.h"
#include <testvaluesetter.h>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

constexpr int clipLen = 2000;

QTEST_MAIN(test_vector_type)

void test_vector_type::setStar()
{
    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorType type = VectorSettingsUser::VectorType::STAR;
    vectorPainter.getVectorSettings()->m_user.setVectorType(type);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorType(), type);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_type::setStarNoValues()
{
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_user.setVectorType(VectorSettingsUser::VectorType::STAR);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_type::setTriangle()
{
    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorType type = VectorSettingsUser::VectorType::TRIANGLE;
    vectorPainter.getVectorSettings()->m_user.setVectorType(type);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorType(), type);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_type::setTriangleNoCurrent()
{
    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_user.setVectorType(VectorSettingsUser::VectorType::TRIANGLE);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, 0, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_type::set3Wire()
{
    const float nomValue = 30;
    const float angle = 0;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorType type = VectorSettingsUser::VectorType::THREE_PHASE;
    vectorPainter.getVectorSettings()->m_user.setVectorType(type);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorType(), type);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}
