#ifndef TEST_TIMEZONE_STATE_CONTROLLER_H
#define TEST_TIMEZONE_STATE_CONTROLLER_H

#include "testtimedate1connection.h"
#include "timezonestatecontroller.h"

class test_timezone_state_controller : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void getTimezoneConnectionStartEarly();
    void getTimezoneConnectionStartLate();

    void getRegionDefaultConnectionStartEarly();
    void getRegionDefaultChangedConnectionStartEarly();
    void getRegionDefaultConnectionStartLate();
    void getRegionDefaultChangedConnectionStartLate();

    void getCityDefaultConnectionStartEarly();
    void getCityDefaultChangedConnectionStartEarly();
    void getCityDefaultConnectionStartLate();
    void getCityDefaultChangedConnectionStartLate();

    void setSameRegion();
    void changeRegionValid();
    void tryChangeRegionInvalid();
    void tryChangeRegionEmpty();
    void changeRegionValidCausesEmptyCity();

    void setSameCity();
    void changeCityValid();
    void tryChangeCityInvalid();
    void tryChangeCityNotInRegion();
    void tryChangeCityEmpty();

    void getCanApplyEarly();
    void getCanApplyLate();
    void validRegionChangesCanApply();
    void invalidRegionKeepsCanApply();
    void validCityChangesCanApply();
    void invalidCityKeepsCanApply();

    void getCanUndoEarly();
    void getCanUndoLate();
    void validRegionChangesCanUndo();
    void invalidRegionKeepsCanUndo();
    void validCityChangesCanUndo();
    void invalidCityKeepsCanUndo();

    void handleInitialThenTimezoneChange();
    void handleChangeRegionThenTimezoneChange();
    void handleChangeRegionChangeCityThenTimezoneChangeToSame();
    void handleChangeRegionChangeCityThenTimezoneChangeToSameRegionDifferentCity();
    void handleChangeRegionChangeCityThenTimezoneChangeToDiffentRegionDifferentCity();

    void doUndoOnUnchanged();
    void doUndoAfterCityChange();
    void doUndoAfterRegionChange();
    void doUndoAfterRegionAndCityChange();

    void doApplyOnUnchanged();
    void setAllTimezonesViaController();
private:
    void spyControllerSignals(TimezoneStateController *controller, QStringList &signalNameList);
    std::shared_ptr<TestTimedate1Connection> m_timeDateConnection;
};

#endif // TEST_TIMEZONE_STATE_CONTROLLER_H
