#ifndef TEST_TIMEZONE_MODEL_BASE_H
#define TEST_TIMEZONE_MODEL_BASE_H

#include "timezonetranslations.h"
#include "abstracttimedate1connection.h"
#include <memory>

class test_timezone_model_base : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void connectionStartEarly();
    void connectionStartLate();

    void checkTimezones();
    void checkTimezonesTranslatedNoTranslationSet();
    void checkTimezonesTranslatedTranslationSetEarly();
    void checkTimezonesTranslatedTranslationSetLate();
    void checkRegion();
    void checkRegionTranslated();
    void checkCityOrCountry();
    void checkCityOrCountryTranslated();

    void initialRegionAndCityEarly();
    void initialRegionAndCityLate();

    void sameRegionNoChange();
    void changeRegionValid();
    void changeRegionInvalid();

    void sameCityNoChange();
    void changeCityInValid();
    void changeCityValidButNotInSelectedRegion();
    void changeCityValid();

    void defaultCanApplyEarly();
    void defaultCanApplyLate();
    void validRegionChangesCanApply();
    void invalidRegionKeepsCanApply();
    void validCityChangesCanApply();
    void invalidCityKeepsCanApply();

private:
    std::shared_ptr<TimezoneTranslations> m_translations;
    std::shared_ptr<AbstractTimedate1Connection> m_timeDateConnection;
};

#endif // TEST_TIMEZONE_MODEL_BASE_H
