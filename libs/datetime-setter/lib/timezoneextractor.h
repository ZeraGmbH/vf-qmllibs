#ifndef TIMEZONEEXTRACTOR_H
#define TIMEZONEEXTRACTOR_H

#include <QString>

class TimezoneExtractor
{
public:
    static QString noRegionString();
    static QString noRegionStringTranslated();
    static QString extractRegion(const QString &timezone);
    static QString extractCityOrCountry(const QString &timezone);
};

#endif // TIMEZONEEXTRACTOR_H
