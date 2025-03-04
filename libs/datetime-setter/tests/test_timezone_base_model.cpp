#include "test_timezone_base_model.h"
#include "timezonebasemodel.h"
#include "testtimedate1connection.h"
#include <signalspywaiter.h>
#include <QTest>

QTEST_MAIN(test_timezone_base_model)

static constexpr int waitTimeForStartOrSync = 10;
static constexpr int timezoneCount = 597;

void test_timezone_base_model::earlyConnectionStart()
{
    std::shared_ptr<AbstractTimedate1Connection> conn = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
    QSignalSpy spyTimezonesAvail(conn.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    conn->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    TimezoneBaseModel model(conn);
    QCOMPARE(model.rowCount(), timezoneCount);
}

void test_timezone_base_model::lateConnectionStart()
{
    std::shared_ptr<AbstractTimedate1Connection> conn = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
    QSignalSpy spyTimezonesAvail(conn.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    TimezoneBaseModel model(conn);
    QSignalSpy spyModelAboutToBeReset(&model, &QAbstractItemModel::modelAboutToBeReset);
    QSignalSpy spyModelReset(&model, &QAbstractItemModel::modelReset);

    conn->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);
    QCOMPARE(spyModelAboutToBeReset.count(), 1);
    QCOMPARE(spyModelReset.count(), 1);

    QCOMPARE(model.rowCount(), timezoneCount);
}

void test_timezone_base_model::checkTimezones()
{
    std::shared_ptr<AbstractTimedate1Connection> conn = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
    QSignalSpy spyTimezonesAvail(conn.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    conn->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneBaseModel model(conn);
    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "Africa/Abidjan");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "Africa/Accra");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "Africa/Addis_Ababa");
}

void test_timezone_base_model::checkTimezonesDisplayNoTranslationSet()
{
    std::shared_ptr<AbstractTimedate1Connection> conn = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
    QSignalSpy spyTimezonesAvail(conn.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    conn->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneBaseModel model(conn);
    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Africa/Abidjan");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Africa/Accra");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Africa/Addis_Ababa");
}

void test_timezone_base_model::checkTimezonesDisplayTranslationSet()
{
    std::shared_ptr<AbstractTimedate1Connection> conn = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
    QSignalSpy spyTimezonesAvail(conn.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    conn->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneBaseModel model(conn);
    QSignalSpy spyModelAboutToBeReset(&model, &QAbstractItemModel::modelAboutToBeReset);
    QSignalSpy spyModelReset(&model, &QAbstractItemModel::modelReset);
    model.setLanguage("de_DE");
    QCOMPARE(spyModelAboutToBeReset.count(), 1);
    QCOMPARE(spyModelReset.count(), 1);

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Afrika/Abidjan");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Afrika/Accra");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Afrika/Addis_Abeba");
}
