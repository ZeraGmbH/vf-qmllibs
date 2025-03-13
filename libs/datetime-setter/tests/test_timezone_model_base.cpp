#include "test_timezone_model_base.h"
#include "timezonemodelbase.h"
#include "testtimedate1connection.h"
#include "timezonetranslations.h"
#include <signalspywaiter.h>
#include <QTest>

QTEST_MAIN(test_timezone_model_base)

static constexpr int waitTimeForStartOrSync = 10;
static constexpr int timezoneCount = 597;

void test_timezone_model_base::init()
{
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
}

void test_timezone_model_base::connectionStartEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    TimezoneModelBase model(m_timeDateConnection);
    QCOMPARE(model.rowCount(), timezoneCount);
}

void test_timezone_model_base::connectionStartLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    TimezoneModelBase model(m_timeDateConnection);
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

    TimezoneModelBase model(m_timeDateConnection);
    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Africa/Abidjan");
    index = model.index(1, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Africa/Accra");
    index = model.index(2, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Africa/Addis_Ababa");
}


void test_timezone_model_base::checkRegion()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection);

    QModelIndex index;
    index = model.index(0, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Africa/Abidjan");
    QCOMPARE(model.data(index, TimezoneModelBase::RegionRole), "Africa");

    index = model.index(127, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "America/Indiana/Indianapolis");
    QCOMPARE(model.data(index, TimezoneModelBase::RegionRole), "America");

    index = model.index(389, 0);
    QCOMPARE(model.data(index, TimezoneModelBase::TimezoneRole), "Egypt");
    QCOMPARE(model.data(index, TimezoneModelBase::RegionRole), TimezoneTranslations::noRegionString());
}

void test_timezone_model_base::checkCityOrCountry()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection);

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

static const char* defaultRegion = "Europe";
static const char* defaultCity = "Berlin";

void test_timezone_model_base::initialRegionAndCityEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneModelBase model(m_timeDateConnection);

    QCOMPARE(model.getSelectedRegion(), defaultRegion);
    QCOMPARE(model.getSelectedCity(), defaultCity);
}

void test_timezone_model_base::initialRegionAndCityLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    TimezoneModelBase model(m_timeDateConnection);
    QSignalSpy spyRegion(&model, &TimezoneModelBase::sigRegionChanged);
    QSignalSpy spyCity(&model, &TimezoneModelBase::sigCityChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    QCOMPARE(model.getSelectedRegion(), defaultRegion);
    QCOMPARE(model.getSelectedCity(), defaultCity);

    QCOMPARE(spyRegion.count(), 1);
    QCOMPARE(spyCity.count(), 1);
}

void test_timezone_model_base::sameRegionNoChange()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);

    QSignalSpy spyRegionChanged(&model, &TimezoneModelBase::sigRegionChanged);
    QSignalSpy spyCityChanged(&model, &TimezoneModelBase::sigCityChanged);
    model.setSelectedRegion(defaultRegion);

    QCOMPARE(spyRegionChanged.count(), 0);
    QCOMPARE(model.getSelectedRegion(), defaultRegion);
    QCOMPARE(spyCityChanged.count(), 0);
    QCOMPARE(model.getSelectedCity(), defaultCity);
}

void test_timezone_model_base::changeRegionValid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);

    QSignalSpy spyRegionChanged(&model, &TimezoneModelBase::sigRegionChanged);
    QSignalSpy spyCityChanged(&model, &TimezoneModelBase::sigCityChanged);
    model.setSelectedRegion("Asia");

    QCOMPARE(spyRegionChanged.count(), 1);
    QCOMPARE(model.getSelectedRegion(), "Asia");
    QCOMPARE(spyCityChanged.count(), 1);
    QCOMPARE(model.getSelectedCity(), ""); // Change region unselects city
}

void test_timezone_model_base::changeRegionInvalid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);

    QSignalSpy spyRegionChanged(&model, &TimezoneModelBase::sigRegionChanged);
    QSignalSpy spyCityChanged(&model, &TimezoneModelBase::sigCityChanged);
    model.setSelectedRegion("Foo");

    QCOMPARE(spyRegionChanged.count(), 0);
    QCOMPARE(model.getSelectedRegion(), defaultRegion);
    QCOMPARE(spyCityChanged.count(), 0);
    QCOMPARE(model.getSelectedCity(), defaultCity);
}

void test_timezone_model_base::sameCityNoChange()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);

    QSignalSpy spyRegionChanged(&model, &TimezoneModelBase::sigRegionChanged);
    QSignalSpy spyCityChanged(&model, &TimezoneModelBase::sigCityChanged);
    model.setSelectedCity(defaultCity);

    QCOMPARE(spyRegionChanged.count(), 0);
    QCOMPARE(model.getSelectedRegion(), defaultRegion);
    QCOMPARE(spyCityChanged.count(), 0);
    QCOMPARE(model.getSelectedCity(), defaultCity);
}

void test_timezone_model_base::changeCityInValid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);

    QSignalSpy spyRegionChanged(&model, &TimezoneModelBase::sigRegionChanged);
    QSignalSpy spyCityChanged(&model, &TimezoneModelBase::sigCityChanged);
    model.setSelectedCity("foo");

    QCOMPARE(spyRegionChanged.count(), 0);
    QCOMPARE(model.getSelectedRegion(), defaultRegion);
    QCOMPARE(spyCityChanged.count(), 0);
    QCOMPARE(model.getSelectedCity(), defaultCity);
}

void test_timezone_model_base::changeCityValidButNotInSelectedRegion()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);

    QSignalSpy spyRegionChanged(&model, &TimezoneModelBase::sigRegionChanged);
    QSignalSpy spyCityChanged(&model, &TimezoneModelBase::sigCityChanged);
    model.setSelectedCity("Sydney");

    QCOMPARE(spyRegionChanged.count(), 0);
    QCOMPARE(model.getSelectedRegion(), defaultRegion);
    QCOMPARE(spyCityChanged.count(), 0);
    QCOMPARE(model.getSelectedCity(), defaultCity);
}

void test_timezone_model_base::changeCityValid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);

    QSignalSpy spyRegionChanged(&model, &TimezoneModelBase::sigRegionChanged);
    QSignalSpy spyCityChanged(&model, &TimezoneModelBase::sigCityChanged);
    model.setSelectedCity("Rome");

    QCOMPARE(spyRegionChanged.count(), 0);
    QCOMPARE(model.getSelectedRegion(), defaultRegion);
    QCOMPARE(spyCityChanged.count(), 1);
    QCOMPARE(model.getSelectedCity(), "Rome");
}

void test_timezone_model_base::defaultCanApplyEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);
    QCOMPARE(model.canApply(), false);
}

void test_timezone_model_base::defaultCanApplyLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    TimezoneModelBase model(m_timeDateConnection);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(model.canApply(), false);
}

void test_timezone_model_base::validRegionChangesCanApply()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);

    QSignalSpy spyCanApplyChanged(&model, &TimezoneModelBase::sigCanApplyChanged);

    // change to valid city -> apply ON
    model.setSelectedCity("Rome");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(model.canApply(), true);

    // change to valid regiom -> apply OFF (no city selected)
    model.setSelectedRegion("Asia");
    QCOMPARE(spyCanApplyChanged.count(), 2);
    QCOMPARE(model.canApply(), false);
}

void test_timezone_model_base::invalidRegionKeepsCanApply()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);

    QSignalSpy spyCanApplyChanged(&model, &TimezoneModelBase::sigCanApplyChanged);

    // change to valid city -> apply ON
    model.setSelectedCity("Rome");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(model.canApply(), true);

    // try change to invalid regiom -> apply remains ON
    model.setSelectedRegion("foo");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(model.canApply(), true);
}

void test_timezone_model_base::validCityChangesCanApply()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);

    QSignalSpy spyCanApplyChanged(&model, &TimezoneModelBase::sigCanApplyChanged);

    model.setSelectedCity("Rome");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(model.canApply(), true);
}

void test_timezone_model_base::invalidCityKeepsCanApply()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneModelBase model(m_timeDateConnection);

    QSignalSpy spyCanApplyChanged(&model, &TimezoneModelBase::sigCanApplyChanged);

    model.setSelectedCity("foo");
    QCOMPARE(spyCanApplyChanged.count(), 0);
    QCOMPARE(model.canApply(), false);

    model.setSelectedCity("Rome");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(model.canApply(), true);

    model.setSelectedCity("foo");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(model.canApply(), true);
}
