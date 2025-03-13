#ifndef TEST_TIMEZONE_MODEL_CITY_FILTERED_H
#define TEST_TIMEZONE_MODEL_CITY_FILTERED_H

#include "timezonemodelcityfiltered.h"
#include <memory>

class test_timezone_model_city_filtered : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void initialNoRegion();
    void moveToEurope();
    void moveToAsia();
    void moveToPacific();
    void moveToAsiaChangeLanguageDe();
    void asiaAndLanguageDeThenStart();
    void languageDeMoveToPacificChange();
    void checkMaxCities();
private:
    bool checkDefaults(TimezoneModelCityFiltered &model);
    QStringList fetchFilteredAndSortedCities(TimezoneModelCityFiltered &model);
    bool checkProperSort(const QStringList &cities);

    std::shared_ptr<TimezoneTranslations> m_translations;
    std::shared_ptr<AbstractTimedate1Connection> m_timeDateConnection;
    std::shared_ptr<TimezoneStateController> m_timezoneController;
};

#endif // TEST_TIMEZONE_MODEL_CITY_FILTERED_H
