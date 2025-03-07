#include "timezonemodelcityfiltered.h"
#include "timezonemodelbase.h"
#include "timezoneextractor.h"
#include <QMap>

TimezoneModelCityFiltered::TimezoneModelCityFiltered(std::shared_ptr<TimezoneModelBase> sourceModel) :
    m_sourceModel(sourceModel),
    m_region(TimezoneExtractor::noRegionString())
{
    fillModel();
    connect(m_sourceModel.get(), &QAbstractItemModel::modelReset,
            this, &TimezoneModelCityFiltered::fillModel);
}

void TimezoneModelCityFiltered::setRegion(const QString &region)
{
    if (m_region != region) {
        m_region = region;
        fillModel();
    }
}

QHash<int, QByteArray> TimezoneModelCityFiltered::roleNames() const
{
    static QHash<int, QByteArray> roles {
        { TimezoneRole, "timezone" },
        { CityOrCountryRoleTranslated, "cityorcountrytranslated"}
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
    case CityOrCountryRoleTranslated:
        return timezone.m_cityTranslated;
    }
    return QVariant();
}

void TimezoneModelCityFiltered::fillModel()
{
    int timezoneCount = m_sourceModel->rowCount();
    QMap<QString /* cityTranslated */, QString /*timezone */> citySortedTimezones;
    for (int i=0; i<timezoneCount; ++i) {
        QModelIndex index = m_sourceModel->index(i, 0);
        const QString region = m_sourceModel->data(index, TimezoneModelBase::RegionRole).toString();
        if (region == m_region) {
            const QString timezone = m_sourceModel->data(index, TimezoneModelBase::TimezoneRole).toString();
            const QString cityTr = m_sourceModel->data(index, TimezoneModelBase::CityOrCountryRoleTranslated).toString();
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
