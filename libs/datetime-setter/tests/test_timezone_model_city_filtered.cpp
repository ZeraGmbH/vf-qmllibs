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
}

void test_timezone_model_city_filtered::initialDefaultRegion()
{
    QVERIFY(initConnectionAndController());
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
    QVERIFY(initConnectionAndController());
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
    QVERIFY(initConnectionAndController());
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
    QVERIFY(initConnectionAndController());
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
    QVERIFY(initConnectionAndController());
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
    QVERIFY(initConnectionAndController());
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
    QVERIFY(initConnectionAndController());
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

void test_timezone_model_city_filtered::initialIndexEarly()
{
    QVERIFY(initConnectionAndController());
    std::shared_ptr<TimezoneStateController> tzController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    TimezoneModelCityFiltered model(tzController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelCityFiltered::sigSelectedIndexChanged);

    QCOMPARE(spyModelIndexChanged.count(), 0);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelCityFiltered::CityRoleTranslated), TestTimedate1Connection::getDefaultCity());
}

void test_timezone_model_city_filtered::initialIndexLate()
{
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
    m_timezoneController = std::make_shared<TimezoneStateController>(m_timeDateConnection);

    TimezoneModelCityFiltered model(m_timezoneController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelCityFiltered::sigSelectedIndexChanged);

    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    QCOMPARE(spyTimezonesAvail.count(), 1);

    QCOMPARE(spyModelIndexChanged.count(), 1);
    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelCityFiltered::CityRoleTranslated), TestTimedate1Connection::getDefaultCity());
}

void test_timezone_model_city_filtered::setIndex0()
{
    QVERIFY(initConnectionAndController());
    QSignalSpy citySpy(m_timezoneController.get(), &TimezoneStateController::sigCityChanged);
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelCityFiltered::sigSelectedIndexChanged);

    model.setSelectedIndex(0);
    QCOMPARE(spyModelIndexChanged.count(), 1);
    QCOMPARE(citySpy.count(), 1);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelCityFiltered::CityRoleTranslated), "Amsterdam");
}

void test_timezone_model_city_filtered::setIndexLast()
{
    QVERIFY(initConnectionAndController());
    QSignalSpy citySpy(m_timezoneController.get(), &TimezoneStateController::sigCityChanged);
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelCityFiltered::sigSelectedIndexChanged);

    model.setSelectedIndex(model.rowCount()-1);
    QCOMPARE(spyModelIndexChanged.count(), 1);
    QCOMPARE(citySpy.count(), 1);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelCityFiltered::CityRoleTranslated), "Zurich");
}

void test_timezone_model_city_filtered::setIndexOutOfLimitMinusOne()
{
    QVERIFY(initConnectionAndController());
    QSignalSpy citySpy(m_timezoneController.get(), &TimezoneStateController::sigCityChanged);
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelCityFiltered::sigSelectedIndexChanged);

    model.setSelectedIndex(-1);
    QCOMPARE(spyModelIndexChanged.count(), 0);
    QCOMPARE(citySpy.count(), 0);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelCityFiltered::CityRoleTranslated), TestTimedate1Connection::getDefaultCity());
}

void test_timezone_model_city_filtered::setIndexOutOfLimitLarge()
{
    QVERIFY(initConnectionAndController());
    QSignalSpy citySpy(m_timezoneController.get(), &TimezoneStateController::sigCityChanged);
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelCityFiltered::sigSelectedIndexChanged);

    model.setSelectedIndex(10000);
    QCOMPARE(spyModelIndexChanged.count(), 0);
    QCOMPARE(citySpy.count(), 0);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelCityFiltered::CityRoleTranslated), TestTimedate1Connection::getDefaultCity());
}

void test_timezone_model_city_filtered::setIndexSameNoChange()
{
    QVERIFY(initConnectionAndController());
    QSignalSpy citySpy(m_timezoneController.get(), &TimezoneStateController::sigCityChanged);
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelCityFiltered::sigSelectedIndexChanged);

    model.setSelectedIndex(model.getSelectedIndex());
    QCOMPARE(spyModelIndexChanged.count(), 0);
    QCOMPARE(citySpy.count(), 0);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelCityFiltered::CityRoleTranslated), TestTimedate1Connection::getDefaultCity());
}

void test_timezone_model_city_filtered::setIndexTwice()
{
    QVERIFY(initConnectionAndController());
    QSignalSpy citySpy(m_timezoneController.get(), &TimezoneStateController::sigCityChanged);
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelCityFiltered::sigSelectedIndexChanged);

    model.setSelectedIndex(0);
    model.setSelectedIndex(model.rowCount()-1);
    QCOMPARE(spyModelIndexChanged.count(), 2);
    QCOMPARE(citySpy.count(), 2);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelCityFiltered::CityRoleTranslated), "Zurich");
}

void test_timezone_model_city_filtered::indexChangeOnLanguageChange()
{
    QVERIFY(initConnectionAndController());
    QSignalSpy citySpy(m_timezoneController.get(), &TimezoneStateController::sigCityChanged);
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelCityFiltered::sigSelectedIndexChanged);

    m_timezoneController->setSelectedRegion("Indian");
    m_timezoneController->setSelectedCity("Christmas");
    QCOMPARE(spyModelIndexChanged.count(), 2);
    QCOMPARE(citySpy.count(), 2);

    int selectedIndexDefault = model.getSelectedIndex();
    m_translations->setLanguage("de_DE"); // Christmas / Weihnachtsinseln is sorted to different places
    int selectedIndexDE = model.getSelectedIndex();
    QVERIFY(selectedIndexDefault != selectedIndexDE);
    QCOMPARE(spyModelIndexChanged.count(), 3);
    QCOMPARE(citySpy.count(), 2);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelCityFiltered::CityRoleTranslated), "Weihnachtsinseln");
}

void test_timezone_model_city_filtered::noIndexChangeOnLanguageChange()
{
    QVERIFY(initConnectionAndController());
    QSignalSpy citySpy(m_timezoneController.get(), &TimezoneStateController::sigCityChanged);
    TimezoneModelCityFiltered model(m_timezoneController, m_translations);
    QSignalSpy spyModelIndexChanged(&model, &TimezoneModelCityFiltered::sigSelectedIndexChanged);

    model.setSelectedIndex(0);
    QCOMPARE(spyModelIndexChanged.count(), 1);
    QCOMPARE(citySpy.count(), 1);

    int selectedIndexDefault = model.getSelectedIndex();
    m_translations->setLanguage("de_DE");
    int selectedIndexDE = model.getSelectedIndex();
    QCOMPARE(selectedIndexDefault, selectedIndexDE);
    QCOMPARE(spyModelIndexChanged.count(), 1);
    QCOMPARE(citySpy.count(), 1);

    int selectedIndex = model.getSelectedIndex();
    QModelIndex index = model.index(selectedIndex, 0);
    QCOMPARE(model.data(index, TimezoneModelCityFiltered::CityRoleTranslated), "Amsterdam");
}

bool test_timezone_model_city_filtered::initConnectionAndController()
{
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
    m_timezoneController = std::make_shared<TimezoneStateController>(m_timeDateConnection);
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
    return spyTimezonesAvail.count() == 1;
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
