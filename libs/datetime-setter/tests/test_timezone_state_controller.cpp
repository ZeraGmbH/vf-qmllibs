#include "test_timezone_state_controller.h"
#include "testtimedate1connection.h"
#include "timezoneextractor.h"
#include <signalspywaiter.h>
#include <timemachineobject.h>
#include <QTest>

QTEST_MAIN(test_timezone_state_controller)

static constexpr int waitTimeForStartOrSync = 10;
static constexpr int timezoneCount = 597;

void test_timezone_state_controller::init()
{
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
}

void test_timezone_state_controller::getTimezonesConnectionStartEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QStringList timezones = controller.getTimezones();
    QCOMPARE(timezones.count(), timezoneCount);
}

void test_timezone_state_controller::getTimezonesConnectionStartLate()
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

void test_timezone_state_controller::getTimzoneDefaultConnectionStartEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QCOMPARE(controller.getSelectedTimezone(), TestTimedate1Connection::getDefaultTimezone());
}

void test_timezone_state_controller::getTimzoneDefaultConnectionStartLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    QCOMPARE(spyTimezoneChanged.count(), 1);
    QCOMPARE(controller.getSelectedTimezone(), TestTimedate1Connection::getDefaultTimezone());
}

void test_timezone_state_controller::getTimzoneDefaultChangedConnectionStartEarly()
{
    m_timeDateConnection->setInitialTimezone("Africa/Casablanca");
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QCOMPARE(controller.getSelectedTimezone(), "Africa/Casablanca");
}

void test_timezone_state_controller::getTimzoneDefaultChangedConnectionStartLate()
{
    m_timeDateConnection->setInitialTimezone("Africa/Casablanca");
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);

    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    QCOMPARE(spyTimezoneChanged.count(), 1);
    QCOMPARE(controller.getSelectedTimezone(), "Africa/Casablanca");
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
    QCOMPARE(controller.getSelectedTimezone(), "Africa/Casablanca");
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
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);
    controller.setSelectedRegion(TestTimedate1Connection::getDefaultRegion());

    QCOMPARE(spyRegionChanged.count(), 0);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, TestTimedate1Connection::getDefaultRegion());

    QCOMPARE(spyTimezoneChanged.count(), 0);
    QString timezone = controller.getSelectedTimezone();
    QCOMPARE(timezone, TestTimedate1Connection::getDefaultTimezone());
}

void test_timezone_state_controller::changeRegionValid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyRegionChanged(&controller, &TimezoneStateController::sigRegionChanged);
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);
    controller.setSelectedRegion("Africa");

    QCOMPARE(spyRegionChanged.count(), 1);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, "Africa");

    QCOMPARE(spyTimezoneChanged.count(), 1);
    QString timezone = controller.getSelectedTimezone();
    QCOMPARE(timezone, "");
}

void test_timezone_state_controller::tryChangeRegionInvalid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyRegionChanged(&controller, &TimezoneStateController::sigRegionChanged);
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);
    controller.setSelectedRegion("foo");

    QCOMPARE(spyRegionChanged.count(), 0);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, TestTimedate1Connection::getDefaultRegion());

    QCOMPARE(spyTimezoneChanged.count(), 0);
    QString timezone = controller.getSelectedTimezone();
    QCOMPARE(timezone, TestTimedate1Connection::getDefaultTimezone());
}

void test_timezone_state_controller::tryChangeRegionEmpty()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyRegionChanged(&controller, &TimezoneStateController::sigRegionChanged);
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);
    controller.setSelectedRegion("");

    QCOMPARE(spyRegionChanged.count(), 0);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, TestTimedate1Connection::getDefaultRegion());

    QCOMPARE(spyTimezoneChanged.count(), 0);
    QString timezone = controller.getSelectedTimezone();
    QCOMPARE(timezone, TestTimedate1Connection::getDefaultTimezone());
}

void test_timezone_state_controller::changeRegionValidCausesEmptyCityAndTimezone()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyRegionChanged(&controller, &TimezoneStateController::sigRegionChanged);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);
    controller.setSelectedRegion("Africa");

    QCOMPARE(spyRegionChanged.count(), 1);
    QString region = controller.getSelectedRegion();
    QCOMPARE(region, "Africa");
    QCOMPARE(spyCityChanged.count(), 1);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, "");

    QCOMPARE(spyTimezoneChanged.count(), 1);
    QString timezone = controller.getSelectedTimezone();
    QCOMPARE(timezone, "");
}

void test_timezone_state_controller::setSameCity()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);
    controller.setSelectedCity(TestTimedate1Connection::getDefaultCity());

    QCOMPARE(spyCityChanged.count(), 0);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, TestTimedate1Connection::getDefaultCity());

    QCOMPARE(spyTimezoneChanged.count(), 0);
    QString timezone = controller.getSelectedTimezone();
    QCOMPARE(timezone, TestTimedate1Connection::getDefaultTimezone());
}

void test_timezone_state_controller::changeCityValid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);
    controller.setSelectedCity("Rome");

    QCOMPARE(spyCityChanged.count(), 1);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, "Rome");

    QCOMPARE(spyTimezoneChanged.count(), 1);
    QString timezone = controller.getSelectedTimezone();
    QCOMPARE(timezone, TestTimedate1Connection::getDefaultRegion() + "/Rome");
}

void test_timezone_state_controller::tryChangeCityInvalid()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);
    controller.setSelectedCity("foo");

    QCOMPARE(spyCityChanged.count(), 0);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, TestTimedate1Connection::getDefaultCity());

    QCOMPARE(spyTimezoneChanged.count(), 0);
    QString timezone = controller.getSelectedTimezone();
    QCOMPARE(timezone, TestTimedate1Connection::getDefaultTimezone());
}

void test_timezone_state_controller::tryChangeCityNotInRegion()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);
    controller.setSelectedCity("Casablanca");

    QCOMPARE(spyCityChanged.count(), 0);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, TestTimedate1Connection::getDefaultCity());

    QCOMPARE(spyTimezoneChanged.count(), 0);
    QString timezone = controller.getSelectedTimezone();
    QCOMPARE(timezone, TestTimedate1Connection::getDefaultTimezone());
}

void test_timezone_state_controller::tryChangeCityEmpty()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);

    TimezoneStateController controller(m_timeDateConnection);
    QSignalSpy spyCityChanged(&controller, &TimezoneStateController::sigCityChanged);
    QSignalSpy spyTimezoneChanged(&controller, &TimezoneStateController::sigSelectedTimezoneChanged);
    controller.setSelectedCity("");

    QCOMPARE(spyCityChanged.count(), 0);
    QString city = controller.getSelectedCity();
    QCOMPARE(city, TestTimedate1Connection::getDefaultCity());

    QCOMPARE(spyTimezoneChanged.count(), 0);
    QString timezone = controller.getSelectedTimezone();
    QCOMPARE(timezone, TestTimedate1Connection::getDefaultTimezone());
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

void test_timezone_state_controller::getCanUndoEarly()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);
    QCOMPARE(controller.canUndo(), false);
}

void test_timezone_state_controller::getCanUndoLate()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    TimezoneStateController controller(m_timeDateConnection);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(controller.canUndo(), false);
}

void test_timezone_state_controller::validRegionChangesCanUndo()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    QSignalSpy spyCanUndoChanged(&controller, &TimezoneStateController::sigCanUndoChanged);

    controller.setSelectedRegion("Asia");
    QCOMPARE(spyCanUndoChanged.count(), 1);
    QCOMPARE(controller.canUndo(), true);
}

void test_timezone_state_controller::invalidRegionKeepsCanUndo()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    QSignalSpy spyCanUndoChanged(&controller, &TimezoneStateController::sigCanUndoChanged);

    controller.setSelectedRegion("foo");
    QCOMPARE(spyCanUndoChanged.count(), 0);
    QCOMPARE(controller.canUndo(), false);
}

void test_timezone_state_controller::validCityChangesCanUndo()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    QSignalSpy spyCanUndoChanged(&controller, &TimezoneStateController::sigCanUndoChanged);

    controller.setSelectedCity("Rome");
    QCOMPARE(spyCanUndoChanged.count(), 1);
    QCOMPARE(controller.canUndo(), true);
}

void test_timezone_state_controller::invalidCityKeepsCanUndo()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    QSignalSpy spyCanUndoChanged(&controller, &TimezoneStateController::sigCanUndoChanged);

    controller.setSelectedCity("foo");
    QCOMPARE(spyCanUndoChanged.count(), 0);
    QCOMPARE(controller.canUndo(), false);

    controller.setSelectedCity("Rome");
    QCOMPARE(spyCanUndoChanged.count(), 1);
    QCOMPARE(controller.canUndo(), true);

    controller.setSelectedCity("foo");
    QCOMPARE(spyCanUndoChanged.count(), 1);
    QCOMPARE(controller.canUndo(), true);
}

void test_timezone_state_controller::handleInitialThenTimezoneChange()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    QStringList signalNamesReceived;
    spyControllerSignals(&controller, signalNamesReceived);
    m_timeDateConnection->setTimezone("Atlantic/Madeira");
    TimeMachineObject::feedEventLoop();

    QCOMPARE(signalNamesReceived.count(), 2);
    QCOMPARE(signalNamesReceived[0], "sigRegionChanged");
    QCOMPARE(signalNamesReceived[1], "sigCityChanged");
    QCOMPARE(controller.getSelectedRegion(), "Atlantic");
    QCOMPARE(controller.getSelectedCity(), "Madeira");
    QCOMPARE(controller.canUndo(), false);
    QCOMPARE(controller.canApply(), false);
}

void test_timezone_state_controller::handleChangeRegionThenTimezoneChange()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    controller.setSelectedRegion("Atlantic");
    QCOMPARE(controller.getSelectedRegion(), "Atlantic");
    QCOMPARE(controller.getSelectedCity(), "");
    QCOMPARE(controller.canUndo(), true);
    QCOMPARE(controller.canApply(), false);

    QStringList signalNamesReceived;
    spyControllerSignals(&controller, signalNamesReceived);
    m_timeDateConnection->setTimezone("Atlantic/Madeira");
    TimeMachineObject::feedEventLoop();

    QCOMPARE(signalNamesReceived.count(), 2);
    QCOMPARE(signalNamesReceived[0], "sigCityChanged");
    QCOMPARE(signalNamesReceived[1], "sigCanUndoChanged");
    QCOMPARE(controller.getSelectedRegion(), "Atlantic");
    QCOMPARE(controller.getSelectedCity(), "Madeira");
    QCOMPARE(controller.canUndo(), false);
    QCOMPARE(controller.canApply(), false);
}

void test_timezone_state_controller::handleChangeRegionChangeCityThenTimezoneChangeToSame()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    controller.setSelectedRegion("Atlantic");
    controller.setSelectedCity("Madeira");
    QCOMPARE(controller.getSelectedRegion(), "Atlantic");
    QCOMPARE(controller.getSelectedCity(), "Madeira");
    QCOMPARE(controller.canUndo(), true);
    QCOMPARE(controller.canApply(), true);

    QStringList signalNamesReceived;
    spyControllerSignals(&controller, signalNamesReceived);
    m_timeDateConnection->setTimezone("Atlantic/Madeira");
    TimeMachineObject::feedEventLoop();

    QCOMPARE(signalNamesReceived.count(), 2);
    QCOMPARE(signalNamesReceived[0], "sigCanUndoChanged");
    QCOMPARE(signalNamesReceived[1], "sigCanApplyChanged");
    QCOMPARE(controller.getSelectedRegion(), "Atlantic");
    QCOMPARE(controller.getSelectedCity(), "Madeira");
    QCOMPARE(controller.canUndo(), false);
    QCOMPARE(controller.canApply(), false);
}

void test_timezone_state_controller::handleChangeRegionChangeCityThenTimezoneChangeToSameRegionDifferentCity()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    controller.setSelectedRegion("Atlantic");
    controller.setSelectedCity("Madeira");
    QCOMPARE(controller.getSelectedRegion(), "Atlantic");
    QCOMPARE(controller.getSelectedCity(), "Madeira");
    QCOMPARE(controller.canUndo(), true);
    QCOMPARE(controller.canApply(), true);

    QStringList signalNamesReceived;
    spyControllerSignals(&controller, signalNamesReceived);
    m_timeDateConnection->setTimezone("Atlantic/Cape_Verde");
    TimeMachineObject::feedEventLoop();

    QCOMPARE(signalNamesReceived.count(), 3);
    QCOMPARE(signalNamesReceived[0], "sigCityChanged");
    QCOMPARE(signalNamesReceived[1], "sigCanUndoChanged");
    QCOMPARE(signalNamesReceived[2], "sigCanApplyChanged");
    QCOMPARE(controller.getSelectedRegion(), "Atlantic");
    QCOMPARE(controller.getSelectedCity(), "Cape_Verde");
    QCOMPARE(controller.canUndo(), false);
    QCOMPARE(controller.canApply(), false);
}

void test_timezone_state_controller::handleChangeRegionChangeCityThenTimezoneChangeToDiffentRegionDifferentCity()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    controller.setSelectedRegion("Atlantic");
    controller.setSelectedCity("Madeira");
    QCOMPARE(controller.getSelectedRegion(), "Atlantic");
    QCOMPARE(controller.getSelectedCity(), "Madeira");
    QCOMPARE(controller.canUndo(), true);
    QCOMPARE(controller.canApply(), true);

    QStringList signalNamesReceived;
    spyControllerSignals(&controller, signalNamesReceived);
    m_timeDateConnection->setTimezone("Australia/Sydney");
    TimeMachineObject::feedEventLoop();

    QCOMPARE(signalNamesReceived.count(), 4);
    QCOMPARE(signalNamesReceived[0], "sigRegionChanged");
    QCOMPARE(signalNamesReceived[1], "sigCityChanged");
    QCOMPARE(signalNamesReceived[2], "sigCanUndoChanged");
    QCOMPARE(signalNamesReceived[3], "sigCanApplyChanged");
    QCOMPARE(controller.getSelectedRegion(), "Australia");
    QCOMPARE(controller.getSelectedCity(), "Sydney");
    QCOMPARE(controller.canUndo(), false);
    QCOMPARE(controller.canApply(), false);
}

void test_timezone_state_controller::doUndoOnUnchanged()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    QStringList signalNamesReceived;
    spyControllerSignals(&controller, signalNamesReceived);
    controller.doUndo();

    QCOMPARE(signalNamesReceived.count(), 0);
}

void test_timezone_state_controller::doUndoAfterCityChange()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    controller.setSelectedCity("Brussels");
    QCOMPARE(controller.getSelectedCity(), "Brussels");
    QCOMPARE(controller.canUndo(), true);

    QStringList signalNamesReceived;
    spyControllerSignals(&controller, signalNamesReceived);
    controller.doUndo();

    QCOMPARE(signalNamesReceived.count(), 3);
    QCOMPARE(signalNamesReceived[0], "sigCityChanged");
    QCOMPARE(signalNamesReceived[1], "sigCanUndoChanged");
    QCOMPARE(signalNamesReceived[2], "sigCanApplyChanged");

    QCOMPARE(controller.getSelectedRegion(), "Europe");
    QCOMPARE(controller.getSelectedCity(), "Berlin");
}

void test_timezone_state_controller::doUndoAfterRegionChange()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    controller.setSelectedRegion("Asia");
    QCOMPARE(controller.getSelectedRegion(), "Asia");
    QCOMPARE(controller.canUndo(), true);

    QStringList signalNamesReceived;
    spyControllerSignals(&controller, signalNamesReceived);
    controller.doUndo();

    QCOMPARE(signalNamesReceived.count(), 3);
    // Apply was not active due to city empty
    QCOMPARE(signalNamesReceived[0], "sigRegionChanged");
    QCOMPARE(signalNamesReceived[1], "sigCityChanged");
    QCOMPARE(signalNamesReceived[2], "sigCanUndoChanged");

    QCOMPARE(controller.getSelectedRegion(), "Europe");
    QCOMPARE(controller.getSelectedCity(), "Berlin");
}

void test_timezone_state_controller::doUndoAfterRegionAndCityChange()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    controller.setSelectedRegion("Asia");
    QCOMPARE(controller.getSelectedRegion(), "Asia");
    controller.setSelectedCity("Macao");
    QCOMPARE(controller.getSelectedCity(), "Macao");
    QCOMPARE(controller.canUndo(), true);

    QStringList signalNamesReceived;
    spyControllerSignals(&controller, signalNamesReceived);
    controller.doUndo();

    QCOMPARE(signalNamesReceived.count(), 4);
    QCOMPARE(signalNamesReceived[0], "sigRegionChanged");
    QCOMPARE(signalNamesReceived[1], "sigCityChanged");
    QCOMPARE(signalNamesReceived[2], "sigCanUndoChanged");
    QCOMPARE(signalNamesReceived[3], "sigCanApplyChanged");

    QCOMPARE(controller.getSelectedRegion(), "Europe");
    QCOMPARE(controller.getSelectedCity(), "Berlin");
}

void test_timezone_state_controller::allTimezonesFormControllerCanBeSet()
{
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    TimezoneStateController controller(m_timeDateConnection);

    QStringList failedTimezones;
    const QStringList timezones = controller.getTimezones();
    for (const QString &timezone : timezones) {
        const QString region = TimezoneExtractor::extractRegion(timezone);
        controller.setSelectedRegion(region);
        const QString city = TimezoneExtractor::extractCity(timezone);
        controller.setSelectedCity(city);

        if (!controller.canApply())
            failedTimezones.append(timezone + ": canApply on");
        if (!controller.canUndo())
            failedTimezones.append(timezone + ": canUndo on");
        m_timeDateConnection->setTimezone(controller.getSelectedTimezone());
        TimeMachineObject::feedEventLoop();
        if (controller.canApply())
            failedTimezones.append(timezone + ": canApply off");
        if (controller.canUndo())
            failedTimezones.append(timezone + ": canUndo off");
        if (m_timeDateConnection->getTimeszone() != timezone)
            failedTimezones.append(timezone + ": not set");
    }
    if (!failedTimezones.isEmpty()) {
        QString msg = failedTimezones.join("\n");
        qWarning("Failed to set the following timezones:");
        qWarning("%s", qPrintable(msg));
        QVERIFY(false);
    }
}

void test_timezone_state_controller::spyControllerSignals(TimezoneStateController *controller, QStringList &signalNameList)
{
    connect(controller, &TimezoneStateController::sigCanUndoChanged, [&]() {
        signalNameList.append("sigCanUndoChanged");
    });
    connect(controller, &TimezoneStateController::sigCanApplyChanged, [&]() {
        signalNameList.append("sigCanApplyChanged");
    });
    connect(controller, &TimezoneStateController::sigCityChanged, [&]() {
        signalNameList.append("sigCityChanged");
    });
    connect(controller, &TimezoneStateController::sigRegionChanged, [&]() {
        signalNameList.append("sigRegionChanged");
    });
}
