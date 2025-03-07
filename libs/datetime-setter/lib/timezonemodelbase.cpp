#include "timezonemodelbase.h"
#include "timezoneextractor.h"

TimezoneModelBase::TimezoneModelBase(std::shared_ptr<AbstractTimedate1Connection> timedateConnection,
                                     std::shared_ptr<TimezoneTranslations> translations) :
    m_timedateConnection(timedateConnection),
    m_translations(translations)
{
    fillModelSetDefaultsFromDateTime();
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged,
            this, &TimezoneModelBase::fillModelSetDefaultsFromDateTime);
    connect(m_translations.get(), &TimezoneTranslations::sigLanguageChanged,
            this, &TimezoneModelBase::fillModel);
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
    if (m_selectedCity != city) {
        m_selectedCity = city;
        emit sigCityChanged();
    }
}

bool TimezoneModelBase::canApply() const
{

}

void TimezoneModelBase::doApply()
{

}

QHash<int, QByteArray> TimezoneModelBase::roleNames() const
{
    static QHash<int, QByteArray> roles {
        { TimezoneRole, "timezone" },
        { TimezoneRoleTranslated, "timezonetranslated" },
        { RegionRole, "region"},
        { RegionRoleTranslated, "regiontranslated" },
        { CityOrCountryRole, "cityorcountry"},
        { CityOrCountryRoleTranslated, "cityorcountrytranslated"}
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
    case TimezoneRoleTranslated:
        return m_translations->translate(timezone);
    case RegionRole:
        return regionFromTimezone(timezone, false);
    case RegionRoleTranslated:
        return regionFromTimezone(timezone, true);
    case CityOrCountryRole:
        return cityFromTimezone(timezone);
    case CityOrCountryRoleTranslated:
        return cityFromTimezone(m_translations->translate(timezone));
    }
    return QVariant();
}

void TimezoneModelBase::fillModelSetDefaultsFromDateTime()
{
    fillModel();
    QString timezoneSet = m_timedateConnection->getTimeszone();
    setSelectedRegion(regionFromTimezone(timezoneSet, false));
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

QString TimezoneModelBase::regionFromTimezone(const QString &timezone, bool translate) const
{
    QString region = translate ?
        TimezoneExtractor::extractRegion(m_translations->translate(timezone)) :
        TimezoneExtractor::extractRegion(timezone);

    if (region.isEmpty())
        region = translate ? TimezoneExtractor::noRegionStringTranslated(): TimezoneExtractor::noRegionString();
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
