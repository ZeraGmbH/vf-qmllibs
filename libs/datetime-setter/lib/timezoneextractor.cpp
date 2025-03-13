#include "timezoneextractor.h"
#include <zeratranslation.h>


static const char* noRegionLabel = "other";
static const char* noRegionStr = "<other>";

QString TimezoneExtractor::noRegionString()
{
    return noRegionStr;
}

QString TimezoneExtractor::noRegionStringTranslated()
{
    return QString("<%1>").arg(ZeraTranslation::getInstance()->trValue(noRegionLabel).toString());
}

QString TimezoneExtractor::extractRegion(const QString &timezone)
{
    RegionCity regionCity = split(timezone);
    return regionCity.region;
}

QString TimezoneExtractor::extractCityOrCountry(const QString &timezone)
{
    RegionCity regionCity = split(timezone);
    return regionCity.city;
}

TimezoneExtractor::RegionCity TimezoneExtractor::split(const QString &timezone)
{
    RegionCity regionCity {noRegionString(), timezone};
    QStringList splitList = timezone.split("/");
    if (splitList.count() >=2) {
        QString region = splitList.takeFirst();
        QString city = splitList.join("/");
        if (!region.isEmpty() && !region.endsWith(" ") &&
            !city.isEmpty() && !city.startsWith(" "))
            regionCity = { region, city };
    }
    return regionCity;
}
