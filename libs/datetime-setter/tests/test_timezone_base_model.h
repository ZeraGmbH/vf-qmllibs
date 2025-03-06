#ifndef TEST_TIMEZONE_BASE_MODEL_H
#define TEST_TIMEZONE_BASE_MODEL_H

#include "timezonetranslations.h"
#include "abstracttimedate1connection.h"
#include <memory>

class test_timezone_base_model : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void earlyConnectionStart();
    void lateConnectionStart();
    void checkTimezones();
    void checkTimezonesTranslatedNoTranslationSet();
    void checkTimezonesTranslatedTranslationSetEarly();
    void checkTimezonesTranslatedTranslationSetLate();
    void checkRegion();
    void checkRegionTranslated();
    void checkCityOrCountry();
    void checkCityOrCountryTranslated();
private:
    std::shared_ptr<TimezoneTranslations> m_translations;
    std::shared_ptr<AbstractTimedate1Connection> m_timeDateConnection;
};

#endif // TEST_TIMEZONE_BASE_MODEL_H
