#include "test_vector_diagram_gui.h"
#include "vectortosvgpainter.h"
#include <xmldocumentcompare.h>
#include <testloghelpers.h>
#include <QTest>

QTEST_MAIN(test_vector_diagram_gui)

void test_vector_diagram_gui::initTestCase()
{
    QDir dir;
    dir.mkpath(TEST_SVG_FILE_PATH);
}

void test_vector_diagram_gui::init()
{
    m_generator = std::make_unique<QSvgGenerator>();
    m_generator->setTitle(tr("Test SVG"));
    m_generator->setDescription("test_vector_diagram_gui");
}

void test_vector_diagram_gui::gridOnlySquare()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(200, 200);
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
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

void test_vector_diagram_gui::gridOnlyRectangleWide()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(300, 200);
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
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

void test_vector_diagram_gui::gridOnlyRectangleNarrow()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(200, 300);
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
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
