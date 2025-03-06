#include "test_timezone_model_base.h"
#include "timezonemodelbase.h"
#include "testtimedate1connection.h"
#include "timezoneextractor.h"
#include <signalspywaiter.h>
#include <QTest>

QTEST_MAIN(test_timezone_model_base)

static constexpr int waitTimeForStartOrSync = 10;
static constexpr int timezoneCount = 597;

void test_timezone_model_base::init()
{
    m_translations = std::make_shared<TimezoneTranslations>();
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
}

void test_timezone_model_base::earlyConnectionStart()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    TimezoneModelBase model(m_timeDateConnection, m_translations);
    QCOMPARE(model.rowCount(), timezoneCount);
}

void test_timezone_model_base::lateConnectionStart()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    TimezoneModelBase model(m_timeDateConnection, m_translations);
    QSignalSpy spyModelAboutToBeReset(&model, &QAbstractItemModel::modelAboutToBeReset);
    QSignalSpy spyModelReset(&model, &QAbstractItemModel::modelReset);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);
    QCOMPARE(spyModelAboutToBeReset.count(), 1);
    QCOMPARE(spyModelReset.count(), 1);

    QCOMPARE(model.rowCount(), timezoneCount);
}

void test_timezone_model_base::checkTimezones()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection, m_translations);
    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Africa/Abidjan");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Africa/Accra");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Africa/Addis_Ababa");
}

void test_timezone_model_base::checkTimezonesTranslatedNoTranslationSet()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection, m_translations);
    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Africa/Abidjan");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Africa/Accra");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Africa/Addis_Ababa");
}

void test_timezone_model_base::checkTimezonesTranslatedTranslationSetEarly()
{
    m_translations->setLanguage("de_DE");
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection, m_translations);

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Afrika/Abidjan");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Afrika/Accra");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Afrika/Addis_Abeba");
}

void test_timezone_model_base::checkTimezonesTranslatedTranslationSetLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection, m_translations);
    QSignalSpy spyModelAboutToBeReset(&model, &QAbstractItemModel::modelAboutToBeReset);
    QSignalSpy spyModelReset(&model, &QAbstractItemModel::modelReset);
    m_translations->setLanguage("de_DE");
    QCOMPARE(spyModelAboutToBeReset.count(), 1);
    QCOMPARE(spyModelReset.count(), 1);

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Afrika/Abidjan");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Afrika/Accra");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Afrika/Addis_Abeba");
}

void test_timezone_model_base::checkRegion()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection, m_translations);
    m_translations->setLanguage("de_DE");

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Africa/Abidjan");
    QCOMPARE(model.data(index, TimezoneModelBase::RegionRole), "Africa");

    index = model.index(127, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "America/Indiana/Indianapolis");
    QCOMPARE(model.data(index, TimezoneModelBase::RegionRole), "America");

    index = model.index(389, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Egypt");
    QCOMPARE(model.data(index, TimezoneModelBase::RegionRole), TimezoneExtractor::noRegionString());
}

void test_timezone_model_base::checkRegionTranslated()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection, m_translations);
    m_translations->setLanguage("de_DE");

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Afrika/Abidjan");
    QCOMPARE(model.data(index, TimezoneModelBase::RegionRoleTranslated), "Afrika");

    index = model.index(127, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Amerika/Indiana/Indianapolis");
    QCOMPARE(model.data(index, TimezoneModelBase::RegionRoleTranslated), "Amerika");

    index = model.index(389, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Ägypten");
    QCOMPARE(model.data(index, TimezoneModelBase::RegionRoleTranslated), TimezoneExtractor::noRegionStringTranslated());
}

void test_timezone_model_base::checkCityOrCountry()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection, m_translations);
    m_translations->setLanguage("de_DE");

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Africa/Abidjan");
    QCOMPARE(model.data(index, TimezoneModelBase::CityOrCountryRole), "Abidjan");

    index = model.index(127, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "America/Indiana/Indianapolis");
    QCOMPARE(model.data(index, TimezoneModelBase::CityOrCountryRole), "Indiana/Indianapolis");

    index = model.index(389, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Egypt");
    QCOMPARE(model.data(index, TimezoneModelBase::CityOrCountryRole), "Egypt");

    bool emptyCityFound = false;
    for (int i=0; i<model.rowCount(); ++i) {
        index = model.index(i, 0);
        if (model.data(index, TimezoneModelBase::CityOrCountryRole).toString().isEmpty())
            emptyCityFound = true;
    }
    QCOMPARE(emptyCityFound, false);
}

void test_timezone_model_base::checkCityOrCountryTranslated()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection, m_translations);
    m_translations->setLanguage("de_DE");

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Afrika/Abidjan");
    QCOMPARE(model.data(index, TimezoneModelBase::CityOrCountryRoleTranslated), "Abidjan");

    index = model.index(127, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Amerika/Indiana/Indianapolis");
    QCOMPARE(model.data(index, TimezoneModelBase::CityOrCountryRoleTranslated), "Indiana/Indianapolis");

    index = model.index(389, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRoleTranslated), "Ägypten");
    QCOMPARE(model.data(index, TimezoneModelBase::CityOrCountryRoleTranslated), "Ägypten");

    bool emptyCityFound = false;
    for (int i=0; i<model.rowCount(); ++i) {
        index = model.index(i, 0);
        if (model.data(index, TimezoneModelBase::CityOrCountryRoleTranslated).toString().isEmpty())
            emptyCityFound = true;
    }
    QCOMPARE(emptyCityFound, false);
}

void test_timezone_model_base::initialRegionAndCityEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection, m_translations);

    QCOMPARE(model.getSelectedRegion(), "Europe");
    QCOMPARE(model.getSelectedCity(), "Berlin");
}

void test_timezone_model_base::initialRegionAndCityLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    TimezoneModelBase model(m_timeDateConnection, m_translations);
    QSignalSpy spyRegion(&model, &TimezoneModelBase::sigRegionChanged);
    QSignalSpy spyCity(&model, &TimezoneModelBase::sigCityChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    QCOMPARE(model.getSelectedRegion(), "Europe");
    QCOMPARE(model.getSelectedCity(), "Berlin");

    QCOMPARE(spyRegion.count(), 1);
    QCOMPARE(spyCity.count(), 1);
}
