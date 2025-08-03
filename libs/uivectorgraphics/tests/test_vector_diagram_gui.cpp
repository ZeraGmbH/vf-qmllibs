#include "test_vector_diagram_gui.h"
#include "vectortosvgpainter.h"
#include <cmath>
#include <complex>
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

// We use huge numbers to avoid float/rounding problems and find scalabilty issues
constexpr int clipLenShort = 2000;
constexpr int clipLenLong = 3000;

void test_vector_diagram_gui::gridOnlySquare()
{
    const QString fileBase = QString(QTest::currentTestFunction()) + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
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

    VectorToSvgPainter svgPainter(clipLenLong, clipLenShort);
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

    VectorToSvgPainter svgPainter(clipLenShort, clipLenLong);
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

static QString getNameFomViewType(VectorPainter::VectorView type)
{
    switch (type) {
    case VectorPainter::VectorView::VIEW_STAR:
        return "star";
    case VectorPainter::VectorView::VIEW_TRIANGLE:
        return "triangle";
    case VectorPainter::VectorView::VIEW_THREE_PHASE:
        return "three_phase";
    }
    return QString();
}

Q_DECLARE_METATYPE(VectorPainter::VectorView)

void test_vector_diagram_gui::fullStar_data()
{
    QTest::addColumn<int>("angle");
    QTest::addColumn<VectorPainter::VectorView>("viewType");
    const QVector<int> angles { -30, 0, 30, 90 };
    const QVector<VectorPainter::VectorView> viewTypes {
        VectorPainter::VectorView::VIEW_STAR,
        VectorPainter::VectorView::VIEW_TRIANGLE,
        VectorPainter::VectorView::VIEW_THREE_PHASE
    };
    for (int angle : angles) {
        for (VectorPainter::VectorView viewType : viewTypes) {
            const QString angleLabel = QString("angle-%1").arg(angle);
            const QString typeLabel = QString("type-%1").arg(getNameFomViewType(viewType));
            const QString rowName = QString("%1_%2").arg(angleLabel, typeLabel);
            QTest::newRow(rowName.toUtf8()) << angle << viewType;
        }
    }
}

void test_vector_diagram_gui::fullStar()
{
    QFETCH(int, angle);
    QFETCH(VectorPainter::VectorView, viewType);
    const QString fileBase = QString(QTest::currentTestFunction()) + QTest::currentDataTag() + ".svg";
    QString dumpFile = QString(TEST_SVG_FILE_PATH) + fileBase;

    VectorToSvgPainter svgPainter(clipLenShort, clipLenShort);
    VectorPainter *vectorPainter = svgPainter.getVectorPainter();
    setSymmetricValues(vectorPainter, 230, 5, angle);
    vectorPainter->setVectorView(viewType);
    svgPainter.paintToFile(dumpFile);

    QString dumped = TestLogHelpers::loadFile(dumpFile);
    QString expected = TestLogHelpers::loadFile(QString(":/svgs/") + fileBase);
    XmlDocumentCompare compare;
    bool ok = compare.compareXml(dumped, expected);
    if(!ok)
        TestLogHelpers::compareAndLogOnDiff(expected, dumped);
    QVERIFY(ok);
}

void test_vector_diagram_gui::setSymmetricValues(VectorPainter *painter, double uValue, double iValue, double iAngle)
{
    int dark = 130;
    QVector<QColor> colors{QColor("red").darker(dark), QColor("yellow").darker(dark), QColor("blue").darker(dark),
                           QColor("red").lighter(), QColor("yellow").lighter(), QColor("blue").lighter()};

    constexpr double overload = 1.25;
    double uLen = uValue * M_SQRT2;
    painter->setMaxVoltage(uLen*overload);

    double iLen = iValue * M_SQRT2;
    painter->setMaxCurrent(iLen*overload);

    painter->setPhiOrigin(gradToDeg(90));
    painter->setGridScale(clipLenShort / uLen / 2);
    painter->setCircleValue(uLen / overload);

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

double test_vector_diagram_gui::gradToDeg(double angle)
{
    return 2*M_PI * angle/360;
}
