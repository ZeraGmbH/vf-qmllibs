#include "test_timezone_base_model.h"
#include "timezonebasemodel.h"
#include "testtimedate1connection.h"
#include <signalspywaiter.h>
#include <QTest>

QTEST_MAIN(test_timezone_base_model)

static constexpr int waitTimeForStartOrSync = 10;
static constexpr int timezoneCount = 597;

void test_timezone_base_model::init()
{
    m_translations = std::make_shared<TimezoneTranslations>();
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
}

void test_timezone_base_model::earlyConnectionStart()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    TimezoneBaseModel model(m_timeDateConnection, m_translations);
    QCOMPARE(model.rowCount(), timezoneCount);
}

void test_timezone_base_model::lateConnectionStart()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    TimezoneBaseModel model(m_timeDateConnection, m_translations);
    QSignalSpy spyModelAboutToBeReset(&model, &QAbstractItemModel::modelAboutToBeReset);
    QSignalSpy spyModelReset(&model, &QAbstractItemModel::modelReset);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);
    QCOMPARE(spyModelAboutToBeReset.count(), 1);
    QCOMPARE(spyModelReset.count(), 1);

    QCOMPARE(model.rowCount(), timezoneCount);
}

void test_timezone_base_model::checkTimezones()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneBaseModel model(m_timeDateConnection, m_translations);
    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "Africa/Abidjan");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "Africa/Accra");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "Africa/Addis_Ababa");
}

void test_timezone_base_model::checkTimezonesTranslatedNoTranslationSet()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneBaseModel model(m_timeDateConnection, m_translations);
    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Africa/Abidjan");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Africa/Accra");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Africa/Addis_Ababa");
}

void test_timezone_base_model::checkTimezonesTranslatedTranslationSetEarly()
{
    m_translations->setLanguage("de_DE");
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneBaseModel model(m_timeDateConnection, m_translations);

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Afrika/Abidjan");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Afrika/Accra");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Afrika/Addis_Abeba");
}

void test_timezone_base_model::checkTimezonesTranslatedTranslationSetLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneBaseModel model(m_timeDateConnection, m_translations);
    QSignalSpy spyModelAboutToBeReset(&model, &QAbstractItemModel::modelAboutToBeReset);
    QSignalSpy spyModelReset(&model, &QAbstractItemModel::modelReset);
    m_translations->setLanguage("de_DE");
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

void test_timezone_base_model::checkRegion()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneBaseModel model(m_timeDateConnection, m_translations);
    m_translations->setLanguage("de_DE");

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "Africa/Abidjan");
    QCOMPARE(model.data(index, TimezoneBaseModel::RegionRole), "Africa");

    index = model.index(127, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "America/Indiana/Indianapolis");
    QCOMPARE(model.data(index, TimezoneBaseModel::RegionRole), "America");

    index = model.index(389, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "Egypt");
    QCOMPARE(model.data(index, TimezoneBaseModel::RegionRole), "");
}

void test_timezone_base_model::checkRegionTranslated()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneBaseModel model(m_timeDateConnection, m_translations);
    m_translations->setLanguage("de_DE");

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Afrika/Abidjan");
    QCOMPARE(model.data(index, TimezoneBaseModel::RegionRoleTranslated), "Afrika");

    index = model.index(127, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Amerika/Indiana/Indianapolis");
    QCOMPARE(model.data(index, TimezoneBaseModel::RegionRoleTranslated), "Amerika");

    index = model.index(389, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Ägypten");
    QCOMPARE(model.data(index, TimezoneBaseModel::RegionRoleTranslated), "");
}

void test_timezone_base_model::checkCityOrCountry()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneBaseModel model(m_timeDateConnection, m_translations);
    m_translations->setLanguage("de_DE");

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "Africa/Abidjan");
    QCOMPARE(model.data(index, TimezoneBaseModel::CityOrCountryRole), "Abidjan");

    index = model.index(127, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "America/Indiana/Indianapolis");
    QCOMPARE(model.data(index, TimezoneBaseModel::CityOrCountryRole), "Indiana/Indianapolis");

    index = model.index(389, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRole), "Egypt");
    QCOMPARE(model.data(index, TimezoneBaseModel::CityOrCountryRole), "Egypt");

    bool emptyCityFound = false;
    for (int i=0; i<model.rowCount(); ++i) {
        index = model.index(i, 0);
        if (model.data(index, TimezoneBaseModel::CityOrCountryRole).toString().isEmpty())
            emptyCityFound = true;
    }
    QCOMPARE(emptyCityFound, false);
}

void test_timezone_base_model::checkCityOrCountryTranslated()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneBaseModel model(m_timeDateConnection, m_translations);
    m_translations->setLanguage("de_DE");

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Afrika/Abidjan");
    QCOMPARE(model.data(index, TimezoneBaseModel::CityOrCountryRoleTranslated), "Abidjan");

    index = model.index(127, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Amerika/Indiana/Indianapolis");
    QCOMPARE(model.data(index, TimezoneBaseModel::CityOrCountryRoleTranslated), "Indiana/Indianapolis");

    index = model.index(389, 0);
    QCOMPARE(model.data(index, TimezoneBaseModel::TimezoneRoleTranslated), "Ägypten");
    QCOMPARE(model.data(index, TimezoneBaseModel::CityOrCountryRoleTranslated), "Ägypten");

    bool emptyCityFound = false;
    for (int i=0; i<model.rowCount(); ++i) {
        index = model.index(i, 0);
        if (model.data(index, TimezoneBaseModel::CityOrCountryRoleTranslated).toString().isEmpty())
            emptyCityFound = true;
    }
    QCOMPARE(emptyCityFound, false);
}
