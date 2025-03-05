#include "timezoneextractor.h"

QString TimezoneExtractor::extractRegion(const QString &timezone)
{
    QString region;
    int separatorPos = timezone.indexOf("/");
    if (separatorPos > 0)
        region = timezone.left(separatorPos);
    return region;
}

QString TimezoneExtractor::extractCityOrCountry(const QString &timezone)
{
    QString city = timezone;
    int separatorPos = timezone.indexOf("/");
    if (separatorPos > 0 && separatorPos < timezone.size()-1)
        city = timezone.mid(separatorPos+1);
    return city;
}
