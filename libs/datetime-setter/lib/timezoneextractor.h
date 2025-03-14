#ifndef TIMEZONEEXTRACTOR_H
#define TIMEZONEEXTRACTOR_H

#include <QString>

class TimezoneExtractor
{
public:
    static QString extractRegion(const QString &timezone);
    static QString extractCity(const QString &timezone);
private:
    struct RegionCity {
        QString region;
        QString city;
    };
    static RegionCity split(const QString &timezone);
};

#endif // TIMEZONEEXTRACTOR_H
