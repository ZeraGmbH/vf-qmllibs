#include "timezonemodelbase.h"
#include "timezoneextractor.h"

TimezoneModelBase::TimezoneModelBase(std::shared_ptr<AbstractTimedate1Connection> timedateConnection,
                                     std::shared_ptr<TimezoneTranslations> translations) :
    m_timedateConnection(timedateConnection),
    m_translations(translations)
{
    fillModel();
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged,
            this, &TimezoneModelBase::fillModel);
    connect(m_translations.get(), &TimezoneTranslations::sigLanguageChanged,
            this, &TimezoneModelBase::fillModel);
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
    case RegionRole: {
        QString region = TimezoneExtractor::extractRegion(timezone);
        if(region.isEmpty())
            region = TimezoneExtractor::noRegionString();
        return region;
    }
    case RegionRoleTranslated: {
        QString region = TimezoneExtractor::extractRegion(m_translations->translate(timezone));
        if(region.isEmpty())
            region = TimezoneExtractor::noRegionStringTranslated();
        return region;
    }
    case CityOrCountryRole:
        return TimezoneExtractor::extractCityOrCountry(timezone);
    case CityOrCountryRoleTranslated:
        return TimezoneExtractor::extractCityOrCountry(m_translations->translate(timezone));
    }
    return QVariant();
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
