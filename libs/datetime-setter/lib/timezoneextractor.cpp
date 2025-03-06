#include "timezoneextractor.h"
#include <zeratranslation.h>


static const char* noRegionLabel = "other";

QString TimezoneExtractor::noRegionString()
{
    return QString("<%1>").arg(noRegionLabel);
}

QString TimezoneExtractor::noRegionStringTranslated()
{
    return QString("<%1>").arg(ZeraTranslation::getInstance()->trValue(noRegionLabel).toString());
}

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
