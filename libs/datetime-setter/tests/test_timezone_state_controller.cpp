#include "test_timezone_state_controller.h"
#include "timezonestatecontroller.h"
#include "testtimedate1connection.h"
#include <signalspywaiter.h>
#include <QTest>

QTEST_MAIN(test_timezone_state_controller)

static constexpr int waitTimeForStartOrSync = 10;
static constexpr int timezoneCount = 597;

void test_timezone_state_controller::init()
{
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
}

void test_timezone_state_controller::getTimezoneConnectionStartEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QStringList timezones = controller.getTimezones();
    QCOMPARE(timezones.count(), timezoneCount);
}

void test_timezone_state_controller::getTimezoneConnectionStartLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyTimezonesChanged(&controller, &TimezoneStateController::sigTimezonesChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    QCOMPARE(spyTimezonesChanged.count(), 1);
    QStringList timezones = controller.getTimezones();
    QCOMPARE(timezones.count(), timezoneCount);
}

void test_timezone_state_controller::getRegionDefaultConnectionStartEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, TestTimedate1Connection::getDefaultRegion());
}

void test_timezone_state_controller::getRegionDefaultChangedConnectionStartEarly()
{
    m_timeDateConnection->setInitialTimezone("Africa/Casablanca");
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, "Africa");
}

void test_timezone_state_controller::getRegionDefaultConnectionStartLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyRegionChanged(&controller, &TimezoneStateController::sigRegionChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    QCOMPARE(spyRegionChanged.count(), 1);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, TestTimedate1Connection::getDefaultRegion());
}

void test_timezone_state_controller::getRegionDefaultChangedConnectionStartLate()
{
    m_timeDateConnection->setInitialTimezone("Africa/Casablanca");
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyRegionChanged(&controller, &TimezoneStateController::sigRegionChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    QCOMPARE(spyRegionChanged.count(), 1);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, "Africa");
}

void test_timezone_state_controller::getCityDefaultConnectionStartEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, TestTimedate1Connection::getDefaultCity());
}

void test_timezone_state_controller::getCityDefaultChangedConnectionStartEarly()
{
    m_timeDateConnection->setInitialTimezone("Africa/Casablanca");
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, "Casablanca");
}

void test_timezone_state_controller::getCityDefaultConnectionStartLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    QCOMPARE(spyCityChanged.count(), 1);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, TestTimedate1Connection::getDefaultCity());
}

void test_timezone_state_controller::getCityDefaultChangedConnectionStartLate()
{
    m_timeDateConnection->setInitialTimezone("Africa/Casablanca");
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    QCOMPARE(spyCityChanged.count(), 1);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, "Casablanca");
}

void test_timezone_state_controller::setSameRegion()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyRegionChanged(&controller, &TimezoneStateController::sigRegionChanged);
    controller.setSelectedRegion(TestTimedate1Connection::getDefaultRegion());

    QCOMPARE(spyRegionChanged.count(), 0);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, TestTimedate1Connection::getDefaultRegion());
}

void test_timezone_state_controller::changeRegionValid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyRegionChanged(&controller, &TimezoneStateController::sigRegionChanged);
    controller.setSelectedRegion("Africa");

    QCOMPARE(spyRegionChanged.count(), 1);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, "Africa");
}

void test_timezone_state_controller::tryChangeRegionInvalid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyRegionChanged(&controller, &TimezoneStateController::sigRegionChanged);
    controller.setSelectedRegion("foo");

    QCOMPARE(spyRegionChanged.count(), 0);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, TestTimedate1Connection::getDefaultRegion());
}

void test_timezone_state_controller::tryChangeRegionEmpty()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyRegionChanged(&controller, &TimezoneStateController::sigRegionChanged);
    controller.setSelectedRegion("");

    QCOMPARE(spyRegionChanged.count(), 0);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, TestTimedate1Connection::getDefaultRegion());
}

void test_timezone_state_controller::changeRegionValidCausesEmptyCity()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyRegionChanged(&controller, &TimezoneStateController::sigRegionChanged);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    controller.setSelectedRegion("Africa");

    QCOMPARE(spyRegionChanged.count(), 1);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, "Africa");
    QCOMPARE(spyCityChanged.count(), 1);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, "");
}

void test_timezone_state_controller::setSameCity()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    controller.setSelectedCity(TestTimedate1Connection::getDefaultCity());

    QCOMPARE(spyCityChanged.count(), 0);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, TestTimedate1Connection::getDefaultCity());
}

void test_timezone_state_controller::changeCityValid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    controller.setSelectedCity("Rome");

    QCOMPARE(spyCityChanged.count(), 1);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, "Rome");
}

void test_timezone_state_controller::tryChangeCityInvalid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    controller.setSelectedCity("foo");

    QCOMPARE(spyCityChanged.count(), 0);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, TestTimedate1Connection::getDefaultCity());
}

void test_timezone_state_controller::tryChangeCityNotInRegion()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    controller.setSelectedCity("Casablanca");

    QCOMPARE(spyCityChanged.count(), 0);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, TestTimedate1Connection::getDefaultCity());
}

void test_timezone_state_controller::tryChangeCityEmpty()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    controller.setSelectedCity("");

    QCOMPARE(spyCityChanged.count(), 0);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, TestTimedate1Connection::getDefaultCity());
}

void test_timezone_state_controller::getCanApplyEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);
    QCOMPARE(controller.canApply(), false);
}

void test_timezone_state_controller::getCanApplyLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    TimezoneStateController controller(m_timeDateConnection);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(controller.canApply(), false);
}

void test_timezone_state_controller::validRegionChangesCanApply()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    QSignalSpy spyCanApplyChanged(&controller, &TimezoneStateController::sigCanApplyChanged);

    // change to valid city -> apply ON
    controller.setSelectedCity("Rome");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(controller.canApply(), true);

    // change to valid region -> apply OFF (no city selected)
    controller.setSelectedRegion("Asia");
    QCOMPARE(spyCanApplyChanged.count(), 2);
    QCOMPARE(controller.canApply(), false);
}

void test_timezone_state_controller::invalidRegionKeepsCanApply()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    QSignalSpy spyCanApplyChanged(&controller, &TimezoneStateController::sigCanApplyChanged);

    // change to valid city -> apply ON
    controller.setSelectedCity("Rome");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(controller.canApply(), true);

    // try change to invalid regiom -> apply remains ON
    controller.setSelectedRegion("foo");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(controller.canApply(), true);
}

void test_timezone_state_controller::validCityChangesCanApply()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    QSignalSpy spyCanApplyChanged(&controller, &TimezoneStateController::sigCanApplyChanged);

    controller.setSelectedCity("Rome");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(controller.canApply(), true);
}

void test_timezone_state_controller::invalidCityKeepsCanApply()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    QSignalSpy spyCanApplyChanged(&controller, &TimezoneStateController::sigCanApplyChanged);

    controller.setSelectedCity("foo");
    QCOMPARE(spyCanApplyChanged.count(), 0);
    QCOMPARE(controller.canApply(), false);

    controller.setSelectedCity("Rome");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(controller.canApply(), true);

    controller.setSelectedCity("foo");
    QCOMPARE(spyCanApplyChanged.count(), 1);
    QCOMPARE(controller.canApply(), true);
}
