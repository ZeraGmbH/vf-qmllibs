#ifndef TEST_TIMEZONE_EXTRACTOR_H
#define TEST_TIMEZONE_EXTRACTOR_H

#include <QObject>

class test_timezone_extractor : public QObject
{
    Q_OBJECT
private slots:
    void extractRegionNonEmpty();
    void extractRegionMultipleSeparator();
    void extractRegionEmptyIsOther();
    void extractRegionEmptyIsOtherWithSpacedSeparator();

    void extractCityRegionNonEmpty();
    void extractCityRegionMultipleSeparator();
    void extractCityRegionEmpty();
    void extractCityRegionEmptyWithSpacedSeparator();
};

#endif // TEST_TIMEZONE_EXTRACTOR_H
