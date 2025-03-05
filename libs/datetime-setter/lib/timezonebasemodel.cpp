#include "timezonebasemodel.h"

TimezoneBaseModel::TimezoneBaseModel(std::shared_ptr<AbstractTimedate1Connection> timedateConnection) :
    m_timedateConnection(timedateConnection)
{
    fillModel();
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged,
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
        return m_translation.translate(timezone);
    case RegionRole:
        return extractRegion(timezone);
    case RegionRoleTranslated:
        return extractRegion(m_translation.translate(timezone));
    case CityOrCountryRole:
        return extractCityOrCountry(timezone);
    case CityOrCountryRoleTranslated:
        return extractCityOrCountry(m_translation.translate(timezone));
    }
    return QVariant();
}

void TimezoneBaseModel::setLanguage(const QString &language)
{
    if (m_translation.setLanguage(language))
        fillModel();
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

QString TimezoneBaseModel::extractRegion(const QString &timezone) const
{
    QString region;
    int separatorPos = timezone.indexOf("/");
    if (separatorPos > 0)
        region = timezone.left(separatorPos);
    return region;
}

QString TimezoneBaseModel::extractCityOrCountry(const QString &timezone) const
{
    QString city = timezone;
    int separatorPos = timezone.indexOf("/");
    if (separatorPos > 0 && separatorPos < timezone.size()-1)
        city = timezone.mid(separatorPos+1);
    return city;
}
