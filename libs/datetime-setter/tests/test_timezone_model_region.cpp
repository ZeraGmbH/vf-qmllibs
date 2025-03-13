#include "test_timezone_model_region.h"
#include "timezonemodelregion.h"
#include "testtimedate1connection.h"
#include <signalspywaiter.h>
#include <QTest>

QTEST_MAIN(test_timezone_model_region)

static constexpr int waitTimeForStartOrSync = 10;
static constexpr int timezoneRegionCount = 17;

void test_timezone_model_region::init()
{
    m_translations = std::make_shared<TimezoneTranslations>();
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
}

void test_timezone_model_region::connectionStartEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    TimezoneModelRegion model(tzController, m_translations);
    QStringList regions;
    QModelIndex index;
    for(int i=0; i<model.rowCount(); i++) {
        index = model.index(i, 0);
        regions.append(model.data(index, TimezoneModelRegion::RegionRole).toString());
    }
    qInfo("Timezone regions:");
    qInfo("%s", qPrintable(regions.join("\n")));
    QCOMPARE(model.rowCount(), timezoneRegionCount);
}

void test_timezone_model_region::connectionStartLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    TimezoneModelRegion model(tzController, m_translations);
    QSignalSpy spyModelAboutToBeReset(&model, &QAbstractItemModel::modelAboutToBeReset);
    QSignalSpy spyModelReset(&model, &QAbstractItemModel::modelReset);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);
    QCOMPARE(spyModelAboutToBeReset.count(), 1);
    QCOMPARE(spyModelReset.count(), 1);

    QCOMPARE(model.rowCount(), timezoneRegionCount);
}

void test_timezone_model_region::checkRegions()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    TimezoneModelRegion model(tzController, m_translations);
    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRole), "Africa");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRole), "America");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRole), "Antarctica");
}

void test_timezone_model_region::checkRegionsTranslatedNoTranslationSet()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    TimezoneModelRegion model(tzController, m_translations);
    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), "Africa");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), "America");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), "Antarctica");
}

void test_timezone_model_region::checkRegionsTranslatedTranslationSetEarly()
{
    m_translations->setLanguage("de_DE");
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    TimezoneModelRegion model(tzController, m_translations);

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), "Afrika");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), "Amerika");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), "Antarktis");
}

void test_timezone_model_region::checkRegionsTranslatedTranslationSetLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    TimezoneModelRegion model(tzController, m_translations);

    QSignalSpy spyModelAboutToBeReset(&model, &QAbstractItemModel::modelAboutToBeReset);
    QSignalSpy spyModelReset(&model, &QAbstractItemModel::modelReset);
    m_translations->setLanguage("de_DE");
    QCOMPARE(spyModelAboutToBeReset.count(), 1);
    QCOMPARE(spyModelReset.count(), 1);

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), "Afrika");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), "Amerika");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), "Antarktis");
}
