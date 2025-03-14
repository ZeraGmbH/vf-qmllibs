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

    int rowCount = model.rowCount();
    index = model.index(rowCount-1, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRole), TimezoneTranslations::noRegionString());
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

void test_timezone_model_region::initialIndexEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    TimezoneModelRegion model(tzController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelRegion::sigSelectedIndexChanged);

    QCOMPARE(spyTimezonesAvail.count(), 1);
    QCOMPARE(spyModelIndexChanged.count(), 0);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), TestTimedate1Connection::getDefaultRegion());
}

void test_timezone_model_region::initialIndexLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    TimezoneModelRegion model(tzController, m_translations);
    QCOMPARE(model.getSelectedIndex(), -1);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelRegion::sigSelectedIndexChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    QCOMPARE(spyTimezonesAvail.count(), 1);
    QCOMPARE(spyModelIndexChanged.count(), 1);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), TestTimedate1Connection::getDefaultRegion());
}

void test_timezone_model_region::setIndex0()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    QSignalSpy regionSpy(tzController.get(), &TimezoneStateController::sigRegionChanged);
    TimezoneModelRegion model(tzController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelRegion::sigSelectedIndexChanged);

    QCOMPARE(spyModelIndexChanged.count(), 0);
    QCOMPARE(regionSpy.count(), 0);
    model.setSelectedIndex(0);
    QCOMPARE(spyModelIndexChanged.count(), 1);
    QCOMPARE(regionSpy.count(), 1);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), "Africa");
}

void test_timezone_model_region::setIndexLast()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    QSignalSpy regionSpy(tzController.get(), &TimezoneStateController::sigRegionChanged);
    TimezoneModelRegion model(tzController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelRegion::sigSelectedIndexChanged);

    QCOMPARE(spyModelIndexChanged.count(), 0);
    QCOMPARE(regionSpy.count(), 0);
    model.setSelectedIndex(model.rowCount()-1);
    QCOMPARE(spyModelIndexChanged.count(), 1);
    QCOMPARE(regionSpy.count(), 1);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), TimezoneTranslations::noRegionString());
}

void test_timezone_model_region::setIndexOutOfLimitMinusOne()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    QSignalSpy regionSpy(tzController.get(), &TimezoneStateController::sigRegionChanged);
    TimezoneModelRegion model(tzController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelRegion::sigSelectedIndexChanged);

    model.setSelectedIndex(-1);
    QCOMPARE(spyModelIndexChanged.count(), 0);
    QCOMPARE(regionSpy.count(), 0);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), TestTimedate1Connection::getDefaultRegion());
}

void test_timezone_model_region::setIndexOutOfLimitLarge()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    QSignalSpy regionSpy(tzController.get(), &TimezoneStateController::sigRegionChanged);
    TimezoneModelRegion model(tzController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelRegion::sigSelectedIndexChanged);

    model.setSelectedIndex(10000);
    QCOMPARE(spyModelIndexChanged.count(), 0);
    QCOMPARE(regionSpy.count(), 0);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), TestTimedate1Connection::getDefaultRegion());
}

void test_timezone_model_region::setIndexSameNoChange()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    QSignalSpy regionSpy(tzController.get(), &TimezoneStateController::sigRegionChanged);
    TimezoneModelRegion model(tzController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelRegion::sigSelectedIndexChanged);

    model.setSelectedIndex(model.getSelectedIndex());
    QCOMPARE(spyModelIndexChanged.count(), 0);
    QCOMPARE(regionSpy.count(), 0);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), TestTimedate1Connection::getDefaultRegion());
}

void test_timezone_model_region::setIndexTwice()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    QSignalSpy regionSpy(tzController.get(), &TimezoneStateController::sigRegionChanged);
    TimezoneModelRegion model(tzController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelRegion::sigSelectedIndexChanged);

    QCOMPARE(spyModelIndexChanged.count(), 0);
    QCOMPARE(regionSpy.count(), 0);
    model.setSelectedIndex(0);
    model.setSelectedIndex(model.rowCount()-1);
    QCOMPARE(spyModelIndexChanged.count(), 2);
    QCOMPARE(regionSpy.count(), 2);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), TimezoneTranslations::noRegionString());
}

void test_timezone_model_region::indexChangeOnLanguageChange()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    QSignalSpy regionSpy(tzController.get(), &TimezoneStateController::sigRegionChanged);
    TimezoneModelRegion model(tzController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelRegion::sigSelectedIndexChanged);

    tzController->setSelectedRegion("Canada");
    QCOMPARE(spyModelIndexChanged.count(), 1);
    QCOMPARE(regionSpy.count(), 1);

    int selectedIndexDefault = model.getSelectedIndex();
    m_translations->setLanguage("de_DE"); // Canada / Kanada is sorted to different places
    int selectedIndexDE = model.getSelectedIndex();
    QVERIFY(selectedIndexDefault != selectedIndexDE);
    QCOMPARE(spyModelIndexChanged.count(), 2);
    QCOMPARE(regionSpy.count(), 1);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRoleTranslated), "Kanada");
}

void test_timezone_model_region::noIndexChangeOnLanguageChange()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    QSignalSpy regionSpy(tzController.get(), &TimezoneStateController::sigRegionChanged);
    TimezoneModelRegion model(tzController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelRegion::sigSelectedIndexChanged);

    model.setSelectedIndex(model.rowCount()-1);
    QCOMPARE(spyModelIndexChanged.count(), 1);
    QCOMPARE(regionSpy.count(), 1);

    int selectedIndexDefault = model.getSelectedIndex();
    m_translations->setLanguage("de_DE");

    int selectedIndexDE = model.getSelectedIndex();
    QCOMPARE(selectedIndexDefault, selectedIndexDE);
    QCOMPARE(spyModelIndexChanged.count(), 1);
    QCOMPARE(regionSpy.count(), 1);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    // ZeraTranslation does not change language
    QCOMPARE(model.data(index, TimezoneModelRegion::RegionRole), TimezoneTranslations::noRegionString());
}
