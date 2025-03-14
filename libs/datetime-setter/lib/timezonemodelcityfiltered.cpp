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
    connect(m_timezoneController.get(), &TimezoneStateController::sigCityChanged,
            this, &TimezoneModelCityFiltered::handleCityChange);
    connect(m_translations.get(), &TimezoneTranslations::sigLanguageChanged,
            this, &TimezoneModelCityFiltered::fillModel);
}

QHash<int, QByteArray> TimezoneModelCityFiltered::roleNames() const
{
    static QHash<int, QByteArray> roles {
        { TimezoneRole, "timezone" },
        { CityRoleTranslated, "citytranslated"}
    };
    return roles;
}

int TimezoneModelCityFiltered::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_citiesSorted.count();
}

QVariant TimezoneModelCityFiltered::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= m_citiesSorted.count())
        return QVariant();

    const City &city = m_citiesSorted.at(row);

    switch(role) {
    case TimezoneRole:
        return city.m_timezone;
    case CityRoleTranslated:
        return city.m_cityTranslated;
    }
    return QVariant();
}

int TimezoneModelCityFiltered::getSelectedIndex() const
{
    return m_selectedIndex;
}

void TimezoneModelCityFiltered::setSelectedIndex(int index)
{
    if(index < 0 || index >= m_citiesSorted.count()) {
        qWarning("TimezoneModelCityFiltered::setSelectedIndex out of limit: %i!", index);
        return;
    }
    const QString &newCity = m_citiesSorted[index].m_city;
    m_timezoneController->setSelectedCity(newCity);
}

void TimezoneModelCityFiltered::fillModel()
{
    const QString selectedRegion = m_timezoneController->getSelectedRegion();
    const QStringList& timezones = m_timezoneController->getTimezones();
    QMap<QString /* cityTranslated */, City> citiesSorted;
    for (const QString &timezone : timezones) {
        const QString region = TimezoneExtractor::extractRegion(timezone);
        if (region == selectedRegion) {
            const QString city = TimezoneExtractor::extractCity(timezone);
            const QString cityTr = m_translations->translate(city);
            citiesSorted[cityTr] = { timezone, city, cityTr };
        }
    }

    beginResetModel();
    m_citiesSorted.clear();
    for (auto iter=citiesSorted.constBegin(); iter!=citiesSorted.constEnd(); ++iter)
        m_citiesSorted.append(iter.value());
    endResetModel();
    handleCityChange();
}

void TimezoneModelCityFiltered::handleCityChange()
{
    int newEntry = findSelectedCity();
    if (m_selectedIndex != newEntry) {
        m_selectedIndex = newEntry;
        emit sigSelectedIndexChanged();
    }
}

int TimezoneModelCityFiltered::findSelectedCity() const
{
    const QString selectedCity = m_timezoneController->getSelectedCity();
    for (int i=0; i<m_citiesSorted.count(); ++i) {
        const QString city = m_citiesSorted[i].m_city;
        if(city == selectedCity)
            return i;
    }
    return -1;
}
