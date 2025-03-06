#ifndef TEST_TIMEZONE_MODEL_FILTERED_H
#define TEST_TIMEZONE_MODEL_FILTERED_H

#include "timezonemodelbase.h"
#include "timezonemodelfiltered.h"
#include <QObject>
#include <memory>

class test_timezone_model_filtered : public QObject
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
    bool checkDefaults(TimezoneModelFiltered &model);
    QStringList fetchFilteredAndSortedCities(TimezoneModelFiltered &model);
    bool checkProperSort(const QStringList &cities);

    std::shared_ptr<TimezoneTranslations> m_translations;
    std::shared_ptr<AbstractTimedate1Connection> m_timeDateConnection;
    std::shared_ptr<TimezoneModelBase> m_baseModel;
};

#endif // TEST_TIMEZONE_MODEL_FILTERED_H
