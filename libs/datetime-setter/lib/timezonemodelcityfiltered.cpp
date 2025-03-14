#include "timezonemodelcityfiltered.h"
#include "timezonetranslations.h"
#include "timezoneextractor.h"
#include <QMap>

TimezoneModelCityFiltered::TimezoneModelCityFiltered(std::shared_ptr<TimezoneStateController> timezoneController,
                                                     std::shared_ptr<TimezoneTranslations> translations) :
    m_timezoneController(timezoneController),
    m_translations(translations)
{
    fillModel();
    connect(m_timezoneController.get(), &TimezoneStateController::sigTimezonesChanged,
            this, &TimezoneModelCityFiltered::fillModel);
    connect(m_timezoneController.get(), &TimezoneStateController::sigRegionChanged,
            this, &TimezoneModelCityFiltered::fillModel);
    connect(m_translations.get(), &TimezoneTranslations::sigLanguageChanged,
            this, &TimezoneModelCityFiltered::fillModel);
}

QHash<int, QByteArray> TimezoneModelCityFiltered::roleNames() const
{
    static QHash<int, QByteArray> roles {
        { TimezoneRole, "timezone" },
        { CityRoleTranslated, "cityorcountrytranslated"}
    };
    return roles;
}

int TimezoneModelCityFiltered::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_timezoneFilteredSorted.count();
}

QVariant TimezoneModelCityFiltered::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= m_timezoneFilteredSorted.count())
        return QVariant();

    const Timezone &timezone = m_timezoneFilteredSorted.at(row);

    switch(role) {
    case TimezoneRole:
        return timezone.m_timezone;
    case CityRoleTranslated:
        return timezone.m_cityTranslated;
    }
    return QVariant();
}

void TimezoneModelCityFiltered::fillModel()
{
    const QString selectedRegion = m_timezoneController->getSelectedRegion();
    const QStringList& timezones = m_timezoneController->getTimezones();
    QMap<QString /* cityTranslated */, QString /*timezone */> citySortedTimezones;
    for (const QString &timezone : timezones) {
        const QString region = TimezoneExtractor::extractRegion(timezone);
        if (region == selectedRegion) {
            const QString city = TimezoneExtractor::extractCityOrCountry(timezone);
            const QString cityTr = m_translations->translate(city);
            citySortedTimezones[cityTr] = timezone;
        }
    }

    beginResetModel();
    m_timezoneFilteredSorted.clear();
    for (auto iter=citySortedTimezones.constBegin(); iter!=citySortedTimezones.constEnd(); ++iter) {
        Timezone entry = { iter.value(), iter.key() };
        m_timezoneFilteredSorted.append(entry);
    }
    endResetModel();
}
