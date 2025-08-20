#include "test_vector_label_collision.h"
#include "vectortosvgpainter.h"
#include <testvaluesetter.h>
#include <svgfuzzycompare.h>
#include <testloghelpers.h>
#include <QTest>

QTEST_MAIN(test_vector_label_collision)

constexpr int clipLen = 2000;

void test_vector_label_collision::detectCollisionAllSameAngle()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_layout.setLabelCollisionAvoidance(true);
    QCOMPARE(vectorPainter.getVectorSettings()->m_layout.getLabelCollisionAvoidance(), true);

    TestValueSetter::setVectors(
        &vectorPainter,
        {
            std::polar<float>(1.0, 0.0),
            std::polar<float>(0.9, 0.0),
            std::polar<float>(0.8, 0.0),
            std::polar<float>(0.7, 0.0),
            std::polar<float>(0.6, 0.0),
            std::polar<float>(0.5, 0.0),
        });
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_label_collision::detectCollision_data()
{
    QTest::addColumn<float>("angle");
    QTest::addColumn<float>("length");
    QTest::addColumn<VectorSettingsUser::VectorType>("vectorType");
    QVector<float> angles{0, 2, 88, 90, 92, 118, 120, 122, 208, 210, 212, 238, 240, 242, 268, 270, 272, 328, 330, 332, 358};
    QVector<float> lengths{1, 0.8};
    QVector<VectorSettingsUser::VectorType> vectorTypes{
        VectorSettingsUser::VectorType::STAR,
        VectorSettingsUser::VectorType::TRIANGLE,
        VectorSettingsUser::VectorType::THREE_PHASE };
    for (const float angle : angles) {
        for (const float length : lengths) {
            for (const VectorSettingsUser::VectorType vectorType : vectorTypes) {
                const QString angleLabel = QString("angle-%1").arg(angle);
                const QString lengthLabel = QString("length-%1").arg(length);
                QString vectorTypeLabel;
                switch(vectorType) {
                case VectorSettingsUser::VectorType::STAR:
                    vectorTypeLabel = "vectorType-star";
                    break;
                case VectorSettingsUser::VectorType::TRIANGLE:
                    vectorTypeLabel = "vectorType-triangle";
                    break;
                case VectorSettingsUser::VectorType::THREE_PHASE:
                    vectorTypeLabel = "vectorType-3wire";
                    break;
                }

                //                                              V sequence here is 'convenience' sorted
                const QString rowName = QString("%1_%2_%3").arg(vectorTypeLabel, lengthLabel, angleLabel);
                QTest::newRow(rowName.toUtf8()) << angle << length << vectorType;
            }
        }
    }
}

void test_vector_label_collision::detectCollision()
{
    QFETCH(float, angle);
    QFETCH(float, length);
    QFETCH(VectorSettingsUser::VectorType, vectorType);
    const QString fileBase = QString(QTest::currentTestFunction()) + "_" + QTest::currentDataTag() + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_layout.setLabelCollisionAvoidance(true);

    const float nomValue = 1;
    vectorPainter.getVectorSettings()->m_user.setVectorType(vectorType);
    VectorSettingsLengths &lengthSettings = vectorPainter.getVectorSettings()->m_lengths;
    lengthSettings.setNominalSelection(VectorSettingsLengths::VectorNominals::NOMINAL);
    lengthSettings.setNomCurrent(nomValue);
    lengthSettings.setNomVoltage(nomValue);
    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue*length, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_label_collision::playgroundDebugInterestingCaseSingle()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_layout.setLabelCollisionAvoidance(true);

    const float nomValue = 1;
    vectorPainter.getVectorSettings()->m_user.setVectorType(VectorSettingsUser::VectorType::THREE_PHASE);
    VectorSettingsLengths &lengthSettings = vectorPainter.getVectorSettings()->m_lengths;
    lengthSettings.setNominalSelection(VectorSettingsLengths::VectorNominals::NOMINAL);
    lengthSettings.setNomCurrent(nomValue);
    lengthSettings.setNomVoltage(nomValue);
    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue, 242);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_label_collision::fullMonsterForCinema_data()
{
    // take svgs for every second degree angle to detect surprises in collision algorithm
    QSKIP("This explodes runtime and files created");
    QTest::addColumn<float>("angle");
    QTest::addColumn<float>("length");
    QTest::addColumn<VectorSettingsUser::VectorType>("vectorType");
    QVector<float> lengths{1, 0.8};
    QVector<VectorSettingsUser::VectorType> vectorTypes{
                                                        VectorSettingsUser::VectorType::STAR,
                                                        VectorSettingsUser::VectorType::TRIANGLE,
                                                        VectorSettingsUser::VectorType::THREE_PHASE };
    for(int angle = 0; angle < 360; angle+=2) {
        for (const float length : lengths) {
            for (const VectorSettingsUser::VectorType vectorType : vectorTypes) {
                const QString angleLabel = QString("angle-%1").arg(angle);
                const QString lengthLabel = QString("length-%1").arg(length);
                QString vectorTypeLabel;
                switch(vectorType) {
                case VectorSettingsUser::VectorType::STAR:
                    vectorTypeLabel = "vectorType-star";
                    break;
                case VectorSettingsUser::VectorType::TRIANGLE:
                    vectorTypeLabel = "vectorType-triangle";
                    break;
                case VectorSettingsUser::VectorType::THREE_PHASE:
                    vectorTypeLabel = "vectorType-3wire";
                    break;
                }

                //                                              V sequence here is 'convenience' sorted
                const QString rowName = QString("%1_%2_%3").arg(vectorTypeLabel, lengthLabel, angleLabel);
                QTest::newRow(rowName.toUtf8()) << float(angle) << length << vectorType;
            }
        }
    }

}

void test_vector_label_collision::fullMonsterForCinema()
{
    QSKIP("This explodes runtime and files created");
    QFETCH(float, angle);
    QFETCH(float, length);
    QFETCH(VectorSettingsUser::VectorType, vectorType);
    const QString fileBase = QString(QTest::currentTestFunction()) + "_" + QTest::currentDataTag() + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLen, clipLen);
    VectorPaintController vectorPainter;

    vectorPainter.getVectorSettings()->m_layout.setLabelCollisionAvoidance(true);

    const float nomValue = 1;
    vectorPainter.getVectorSettings()->m_user.setVectorType(vectorType);
    VectorSettingsLengths &lengthSettings = vectorPainter.getVectorSettings()->m_lengths;
    lengthSettings.setNominalSelection(VectorSettingsLengths::VectorNominals::NOMINAL);
    lengthSettings.setNomCurrent(nomValue);
    lengthSettings.setNomVoltage(nomValue);
    TestValueSetter::setSymmetricValues(&vectorPainter, nomValue, nomValue*length, angle);
    svgPainter.paintToFile(dumpFile, &vectorPainter);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    SvgFuzzyCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}
