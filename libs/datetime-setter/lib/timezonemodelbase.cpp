#include "timezonemodelbase.h"
#include "timezoneextractor.h"

TimezoneModelBase::TimezoneModelBase(std::shared_ptr<AbstractTimedate1Connection> timedateConnection) :
    m_timedateConnection(timedateConnection)
{
    fillModelSetDefaultsFromDateTime();
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged,
            this, &TimezoneModelBase::fillModelSetDefaultsFromDateTime);
    connect(this, &TimezoneModelBase::sigCityChanged,
            this, &TimezoneModelBase::handleCityChange);
}

QString TimezoneModelBase::getSelectedRegion() const
{
    return m_selectedRegion;
}

void TimezoneModelBase::setSelectedRegion(const QString &region)
{
    if (m_selectedRegion != region && isValidRegion(region)) {
        m_selectedRegion = region;
        emit sigRegionChanged();
        setSelectedCity("");
    }
}

QString TimezoneModelBase::getSelectedCity() const
{
    return m_selectedCity;
}

void TimezoneModelBase::setSelectedCity(const QString &city)
{
    if (m_selectedCity != city && isValidCity(city)) {
        m_selectedCity = city;
        emit sigCityChanged();
    }
}

bool TimezoneModelBase::canApply() const
{
    return m_canApply;
}

void TimezoneModelBase::doApply()
{

}

QHash<int, QByteArray> TimezoneModelBase::roleNames() const
{
    static QHash<int, QByteArray> roles {
        { TimezoneRole, "timezone" },
        { RegionRole, "region"},
        { CityOrCountryRole, "cityorcountry"}
    };
    return roles;
}

int TimezoneModelBase::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_timezones.count();
}

QVariant TimezoneModelBase::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= m_timezones.count())
        return QVariant();

    const QString &timezone = m_timezones.at(row);

    switch(role) {
    case TimezoneRole:
        return timezone;
    case RegionRole:
        return regionFromTimezone(timezone);
    case CityOrCountryRole:
        return cityFromTimezone(timezone);
    }
    return QVariant();
}

void TimezoneModelBase::fillModelSetDefaultsFromDateTime()
{
    fillModel();
    QString timezoneSet = m_timedateConnection->getTimeszone();
    setSelectedRegion(regionFromTimezone(timezoneSet));
    setSelectedCity(cityFromTimezone(timezoneSet));
}

void TimezoneModelBase::fillModel()
{
    const QStringList availTimezones = m_timedateConnection->getAvailTimezones();
    if (availTimezones.isEmpty())
        return;
    beginResetModel();
    m_timezones = availTimezones;
    endResetModel();
}

void TimezoneModelBase::handleCityChange()
{
    bool newCanApply = !m_selectedCity.isEmpty() &&
                       m_selectedCity != cityFromTimezone(m_timedateConnection->getTimeszone());
    if (m_canApply != newCanApply) {
        m_canApply = newCanApply;
        emit sigCanApplyChanged();
    }
}

QString TimezoneModelBase::regionFromTimezone(const QString &timezone) const
{
    QString region = TimezoneExtractor::extractRegion(timezone);
    if (region.isEmpty())
        region = TimezoneExtractor::noRegionString();
    return region;
}

QString TimezoneModelBase::cityFromTimezone(const QString &timezone) const
{
    return TimezoneExtractor::extractCityOrCountry(timezone);
}

bool TimezoneModelBase::isValidRegion(const QString &region) const
{
    for (const QString &timezone : m_timezones)
        if(region == TimezoneExtractor::extractRegion(timezone))
            return true;
    return false;
}

bool TimezoneModelBase::isValidCity(const QString &city) const
{
    if(city.isEmpty()) // unselect is valid for city (e.g region change)
        return true;
    for (const QString &timezone : m_timezones)
        if(m_selectedRegion == TimezoneExtractor::extractRegion(timezone))
            if(city == TimezoneExtractor::extractCityOrCountry(timezone))
                return true;
    return false;
}
