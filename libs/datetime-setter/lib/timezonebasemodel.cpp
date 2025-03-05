#include "timezonebasemodel.h"
#include "timezoneextractor.h"

TimezoneBaseModel::TimezoneBaseModel(std::shared_ptr<AbstractTimedate1Connection> timedateConnection,
                                     std::shared_ptr<TimezoneTranslations> translations) :
    m_timedateConnection(timedateConnection),
    m_translations(translations)
{
    fillModel();
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged,
            this, &TimezoneBaseModel::fillModel);
    connect(m_translations.get(), &TimezoneTranslations::sigLanguageChanged,
            this, &TimezoneBaseModel::fillModel);
}

QHash<int, QByteArray> TimezoneBaseModel::roleNames() const
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

int TimezoneBaseModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_timezones.count();
}

QVariant TimezoneBaseModel::data(const QModelIndex &index, int role) const
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
        return TimezoneExtractor::extractRegion(timezone);
    case RegionRoleTranslated:
        return TimezoneExtractor::extractRegion(m_translations->translate(timezone));
    case CityOrCountryRole:
        return TimezoneExtractor::extractCityOrCountry(timezone);
    case CityOrCountryRoleTranslated:
        return TimezoneExtractor::extractCityOrCountry(m_translations->translate(timezone));
    }
    return QVariant();
}

void TimezoneBaseModel::fillModel()
{
    const QStringList availTimezones = m_timedateConnection->getAvailTimezones();
    if (availTimezones.isEmpty())
        return;
    beginResetModel();
    m_timezones = availTimezones;
    endResetModel();
}
