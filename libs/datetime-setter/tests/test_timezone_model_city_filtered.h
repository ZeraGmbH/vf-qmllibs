#ifndef TEST_TIMEZONE_MODEL_CITY_FILTERED_H
#define TEST_TIMEZONE_MODEL_CITY_FILTERED_H

#include "timezonemodelcityfiltered.h"
#include "testtimedate1connection.h"

class test_timezone_model_city_filtered : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void initialDefaultRegion();
    void moveToEurope();
    void moveToAsia();
    void moveToPacific();
    void moveToAsiaChangeLanguageDe();
    void asiaAndLanguageDeThenStart();
    void languageDeMoveToPacificChange();
    void checkMaxCities();

    void initialIndexEarly();
    void initialIndexLate();

    void setIndex0();
    void setIndexLast();
    void setIndexOutOfLimitMinusOne();
    void setIndexOutOfLimitLarge();
    void setIndexSameNoChange();
    void setIndexTwice();
    void indexChangeOnLanguageChange();
    void noIndexChangeOnLanguageChange();

private:
    bool initConnectionAndController();
    bool checkDefaults(TimezoneModelCityFiltered &model);
    QStringList fetchFilteredAndSortedCities(TimezoneModelCityFiltered &model);
    bool checkProperSort(const QStringList &cities);

    TimezoneTranslationsPtr m_translations;
    std::shared_ptr<TestTimedate1Connection> m_timeDateConnection;
    TimezoneStateControllerPtr m_timezoneController;
};

#endif // TEST_TIMEZONE_MODEL_CITY_FILTERED_H
