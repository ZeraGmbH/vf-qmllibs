#include "test_vector_standard.h"
#include "vectorpaintcalc.h"
#include "vectorpaintcontroller.h"
#include "vectortosvgpainter.h"
#include <complex>
#include <testvaluesetter.h>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

constexpr int clipLen = 2000;

QTEST_MAIN(test_vector_standard)

void test_vector_standard::setDIN()
{
    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorStandard standard = VectorSettingsUser::VectorStandard::DIN;
    vectorPainter.getVectorSettings()->m_user.setVectorStandard(standard);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorStandard(), standard);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_standard::setDINUAngle()
{
    VectorToSvgPainter svgPainter(clipLen, clipLen);
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

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_standard::setIEC()
{
    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorStandard standard = VectorSettingsUser::VectorStandard::IEC;
    vectorPainter.getVectorSettings()->m_user.setVectorStandard(standard);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorStandard(), standard);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_standard::setANSI()
{
    const float nomValue = 30;
    const float angle = 30;
    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    VectorSettingsUser::VectorStandard standard = VectorSettingsUser::VectorStandard::ANSI;
    vectorPainter.getVectorSettings()->m_user.setVectorStandard(standard);
    QCOMPARE(vectorPainter.getVectorSettings()->m_user.getVectorStandard(), standard);

    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, angle);

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}

void test_vector_standard::setANSIUAngle()
{
    VectorToSvgPainter svgPainter(clipLen, clipLen);
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

    QString dumped = svgPainter.paintByteArray(&vectorPainter);
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QVERIFY(SvgFuzzyCompare::compareXmlSrc(QString("svgs/") + fileBase, dumped, TEST_SRC_DIR));
}
