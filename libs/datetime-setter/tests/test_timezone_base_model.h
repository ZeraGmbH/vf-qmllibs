#ifndef TEST_TIMEZONE_BASE_MODEL_H
#define TEST_TIMEZONE_BASE_MODEL_H

#include "timezonetranslations.h"
#include <QObject>
#include <memory>

class test_timezone_base_model : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void earlyConnectionStart();
    void lateConnectionStart();
    void checkTimezones();
    void checkTimezonesDisplayNoTranslationSet();
    void checkTimezonesDisplayTranslationSet();
    void checkRegion();
    void checkRegionTranslated();
    void checkCityOrCountry();
    void checkCityOrCountryTranslated();
private:
    std::shared_ptr<TimezoneTranslations> m_translations;
};

#endif // TEST_TIMEZONE_BASE_MODEL_H
