#include "timezoneextractor.h"
#include "timezonetranslations.h"
#include <QStringList>

QString TimezoneExtractor::extractRegion(const QString &timezone)
{
    RegionCity regionCity = split(timezone);
    return regionCity.region;
}

QString TimezoneExtractor::extractCity(const QString &timezone)
{
    RegionCity regionCity = split(timezone);
    return regionCity.city;
}

TimezoneExtractor::RegionCity TimezoneExtractor::split(const QString &timezone)
{
    RegionCity regionCity {TimezoneTranslations::noRegionString(), timezone};
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
