#include "test_timezone_model_city_filtered.h"
#include "timezonemodelregion.h"
#include <signalspywaiter.h>
#include <timemachineobject.h>
#include <QTest>

QTEST_MAIN(test_timezone_model_city_filtered)

static constexpr int waitTimeForStartOrSync = 10;
static constexpr int timezoneCountDefault = 64;
static constexpr int timezoneCountAsia = 99;
static constexpr int timezoneCountEurope = timezoneCountDefault;
static constexpr int timezoneCountPacific = 44;

void test_timezone_model_city_filtered::init()
{
    m_translations = std::make_shared<TimezoneTranslations>();
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
    m_timezoneController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);
}

void test_timezone_model_city_filtered::initialDefaultRegion()
{
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);

    qInfo("Default region: %s", qPrintable(m_timezoneController->getSelectedRegion()));
    QStringList cities = fetchFilteredAndSortedCities(model);
    qInfo("Cities:");
    qInfo("%s", qPrintable(cities.join("\n")));

    QVERIFY(checkProperSort(cities));
    QCOMPARE(model.rowCount(), timezoneCountDefault);
    QCOMPARE(cities.contains("Berlin"), true);
    QCOMPARE(cities.contains("Rome"), true);
}

void test_timezone_model_city_filtered::moveToEurope()
{
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);

    m_timezoneController->setSelectedRegion("Europe");

    QStringList cities = fetchFilteredAndSortedCities(model);
    qInfo("Cities:");
    qInfo("%s", qPrintable(cities.join("\n")));

    QVERIFY(checkProperSort(cities));
    QCOMPARE(model.rowCount(), timezoneCountEurope);
    QCOMPARE(cities[0], "Amsterdam");
    QCOMPARE(cities[model.rowCount()-1], "Zurich");
}

void test_timezone_model_city_filtered::moveToAsia()
{
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);

    m_timezoneController->setSelectedRegion("Asia");

    QStringList cities = fetchFilteredAndSortedCities(model);
    qInfo("Cities:");
    qInfo("%s", qPrintable(cities.join("\n")));

    QVERIFY(checkProperSort(cities));
    QCOMPARE(model.rowCount(), timezoneCountAsia);
    QCOMPARE(cities[0], "Aden");
    QCOMPARE(cities[model.rowCount()-1], "Yerevan");
}

void test_timezone_model_city_filtered::moveToPacific()
{
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);

    m_timezoneController->setSelectedRegion("Pacific");

    QStringList cities = fetchFilteredAndSortedCities(model);
    qInfo("Cities:");
    qInfo("%s", qPrintable(cities.join("\n")));

    QVERIFY(checkProperSort(cities));
    QCOMPARE(model.rowCount(), timezoneCountPacific);
    QCOMPARE(cities[0], "Apia");
    QCOMPARE(cities[model.rowCount()-1], "Yap");
}

void test_timezone_model_city_filtered::moveToAsiaChangeLanguageDe()
{
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);

    m_timezoneController->setSelectedRegion("Asia");
    m_translations->setLanguage("de_DE");
    TimeMachineObject::feedEventLoop();

    QStringList cities = fetchFilteredAndSortedCities(model);
    qInfo("Cities:");
    qInfo("%s", qPrintable(cities.join("\n")));

    QVERIFY(checkProperSort(cities));
    QCOMPARE(model.rowCount(), timezoneCountAsia-1); // -1: There is Asia/Calcutta / Asia/Kolkata translated to Asien/Kalkutta !!!;
    QCOMPARE(cities[0], "Aden");
    QCOMPARE(cities[model.rowCount()-1], "Ürümqi");
}

void test_timezone_model_city_filtered::asiaAndLanguageDeThenStart()
{
    m_translations = std::make_shared<TimezoneTranslations>();
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
    m_timezoneController = std::make_shared<TimezoneStateController>(m_timeDateConnection);

    TimezoneModelCityFiltered model(m_timezoneController, m_translations);
    m_timeDateConnection->setInitialTimezone("Asia/Shanghai");
    m_translations->setLanguage("de_DE");

    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    QStringList cities = fetchFilteredAndSortedCities(model);
    qInfo("Cities:");
    qInfo("%s", qPrintable(cities.join("\n")));

    QVERIFY(checkProperSort(cities));
    QCOMPARE(model.rowCount(), timezoneCountAsia-1); // -1: There is Asia/Calcutta / Asia/Kolkata translated to Asien/Kalkutta !!!;
    QCOMPARE(cities[0], "Aden");
    QCOMPARE(cities[model.rowCount()-1], "Ürümqi");
}

void test_timezone_model_city_filtered::languageDeMoveToPacificChange()
{
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);

    m_timezoneController->setSelectedRegion("Pacific");
    m_translations->setLanguage("de_DE");

    QStringList cities = fetchFilteredAndSortedCities(model);
    qInfo("Cities:");
    qInfo("%s", qPrintable(cities.join("\n")));

    QVERIFY(checkProperSort(cities));
    QCOMPARE(model.rowCount(), timezoneCountPacific);
    QCOMPARE(cities[0], "Apia");
    QCOMPARE(cities[model.rowCount()-1], "Yap");
}

static constexpr int timezoneCount = 597;
static constexpr int maxCityCount = 168;

void test_timezone_model_city_filtered::checkMaxCities()
{
    TimezoneModelRegion regionModel(m_timezoneController, m_translations);
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);
    int maxCities = 0;
    QString maxCityRegion;
    int totaltimezoneCount = 0;
    for (int row=0; row<regionModel.rowCount(); row++) {
        QModelIndex index = regionModel.index(row, 0);
        QString region = regionModel.data(index, TimezoneModelRegion::RegionRole).toString();
        m_timezoneController->setSelectedRegion(region);
        int cityCount = model.rowCount();
        totaltimezoneCount += cityCount;
        if (cityCount > maxCities) {
            maxCities = cityCount;
            maxCityRegion = region;
        }
    }
    QCOMPARE(totaltimezoneCount, timezoneCount);
    QCOMPARE(maxCities, maxCityCount);
    QCOMPARE(maxCityRegion, "America"); // of course!!!
}

QStringList test_timezone_model_city_filtered::fetchFilteredAndSortedCities(TimezoneModelCityFiltered &model)
{
    QStringList cities;
    QModelIndex index;
    for(int i=0; i<model.rowCount(); i++) {
        index = model.index(i, 0);
        QString city = model.data(index, TimezoneModelCityFiltered::CityRoleTranslated).toString();
        cities.append(city);
    }
    return cities;
}

bool test_timezone_model_city_filtered::checkProperSort(const QStringList &cities)
{
    QString lastCity;
    bool sortOk = true;
    for (const QString &city : cities) {
        if (city <= lastCity) {
            qWarning("Improper sorted cities at %s / %s", qPrintable(lastCity), qPrintable(city));
            sortOk = false;
        }
    }
    return sortOk;
}
