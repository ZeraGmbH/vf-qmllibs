#include "test_timezone_extractor.h"
#include "timezoneextractor.h"
#include "timezonetranslations.h"
#include <QTest>

QTEST_MAIN(test_timezone_extractor)

void test_timezone_extractor::extractRegionNonEmpty()
{
    QCOMPARE(TimezoneExtractor::extractRegion("Africa/Casablanca"), "Africa");
}

void test_timezone_extractor::extractRegionMultipleSeparator()
{
    QCOMPARE(TimezoneExtractor::extractRegion("America/North_Dakota/New_Salem"), "America");
}

void test_timezone_extractor::extractRegionEmptyIsOther()
{
    QCOMPARE(TimezoneExtractor::extractRegion("Zulu"), TimezoneTranslations::noRegionString());
}

void test_timezone_extractor::extractRegionEmptyIsOtherWithSpacedSeparator()
{
    QCOMPARE(TimezoneExtractor::extractRegion("Scoresbysund / Ittoqqortoormiit"), TimezoneTranslations::noRegionString());
}

void test_timezone_extractor::extractCityRegionNonEmpty()
{
    QCOMPARE(TimezoneExtractor::extractCity("Africa/Casablanca"), "Casablanca");
}

void test_timezone_extractor::extractCityRegionMultipleSeparator()
{
    QCOMPARE(TimezoneExtractor::extractCity("America/North_Dakota/New_Salem"), "North_Dakota/New_Salem");
}

void test_timezone_extractor::extractCityRegionEmpty()
{
    QCOMPARE(TimezoneExtractor::extractCity("Zulu"), "Zulu");
}

void test_timezone_extractor::extractCityRegionEmptyWithSpacedSeparator()
{
    QCOMPARE(TimezoneExtractor::extractCity("Scoresbysund / Ittoqqortoormiit"), "Scoresbysund / Ittoqqortoormiit");
}
