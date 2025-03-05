#include "test_timezone_region_model.h"
#include "timezoneregionmodel.h"
#include "testtimedate1connection.h"
#include <signalspywaiter.h>
#include <QTest>

QTEST_MAIN(test_timezone_region_model)

static constexpr int waitTimeForStartOrSync = 10;
static constexpr int timezoneRegionCount = 17;

void test_timezone_region_model::init()
{
    m_translations = std::make_shared<TimezoneTranslations>();
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
}

void test_timezone_region_model::earlyConnectionStart()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    std::shared_ptr<TimezoneBaseModel> baseModel =
        std::make_shared<TimezoneBaseModel>(m_timeDateConnection, m_translations);
    TimezoneRegionModel model(baseModel);
    QStringList regions;
    QModelIndex index;
    for(int i=0; i<model.rowCount(); i++) {
        index = model.index(i, 0);
        regions.append(model.data(index, TimezoneRegionModel::RegionRole).toString());
    }
    qInfo("Timezone regions:");
    qInfo("%s", qPrintable(regions.join("\n")));
    QCOMPARE(model.rowCount(), timezoneRegionCount);
}

void test_timezone_region_model::lateConnectionStart()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    std::shared_ptr<TimezoneBaseModel> baseModel =
        std::make_shared<TimezoneBaseModel>(m_timeDateConnection, m_translations);
    TimezoneRegionModel model(baseModel);
    QSignalSpy spyModelAboutToBeReset(&model, &QAbstractItemModel::modelAboutToBeReset);
    QSignalSpy spyModelReset(&model, &QAbstractItemModel::modelReset);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);
    QCOMPARE(spyModelAboutToBeReset.count(), 1);
    QCOMPARE(spyModelReset.count(), 1);

    QCOMPARE(model.rowCount(), timezoneRegionCount);
}

void test_timezone_region_model::checkRegions()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    std::shared_ptr<TimezoneBaseModel> baseModel =
        std::make_shared<TimezoneBaseModel>(m_timeDateConnection, m_translations);
    TimezoneRegionModel model(baseModel);
    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneRegionModel::RegionRole), "Africa");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneRegionModel::RegionRole), "America");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneRegionModel::RegionRole), "Antarctica");
}

void test_timezone_region_model::checkRegionsTranslatedNoTranslationSet()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    std::shared_ptr<TimezoneBaseModel> baseModel =
        std::make_shared<TimezoneBaseModel>(m_timeDateConnection, m_translations);
    TimezoneRegionModel model(baseModel);
    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneRegionModel::RegionRoleTranslated), "Africa");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneRegionModel::RegionRoleTranslated), "America");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneRegionModel::RegionRoleTranslated), "Antarctica");
}

void test_timezone_region_model::checkRegionsTranslatedTranslationSet()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    std::shared_ptr<TimezoneBaseModel> baseModel =
        std::make_shared<TimezoneBaseModel>(m_timeDateConnection, m_translations);
    TimezoneRegionModel model(baseModel);

    QSignalSpy spyModelAboutToBeReset(&model, &QAbstractItemModel::modelAboutToBeReset);
    QSignalSpy spyModelReset(&model, &QAbstractItemModel::modelReset);
    m_translations->setLanguage("de_DE");
    QCOMPARE(spyModelAboutToBeReset.count(), 1);
    QCOMPARE(spyModelReset.count(), 1);

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneRegionModel::RegionRoleTranslated), "Afrika");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneRegionModel::RegionRoleTranslated), "Amerika");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneRegionModel::RegionRoleTranslated), "Antarktis");
}
