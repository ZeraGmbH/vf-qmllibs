#include "timezonemodelregion.h"
#include "timezoneextractor.h"

TimezoneModelRegion::TimezoneModelRegion(std::shared_ptr<TimezoneStateController> timezoneController,
                                         std::shared_ptr<TimezoneTranslations> translations) :
    m_timezoneController(timezoneController),
    m_translations(translations)
{
    fillModel();
    connect(m_timezoneController.get(), &TimezoneStateController::sigTimezonesChanged,
            this, &TimezoneModelRegion::fillModel);
    connect(m_translations.get(), &TimezoneTranslations::sigLanguageChanged,
            this, &TimezoneModelRegion::fillModel);
}

QHash<int, QByteArray> TimezoneModelRegion::roleNames() const
{
    static QHash<int, QByteArray> roles {
        { RegionRole, "region"},
        { RegionRoleTranslated, "regiontranslated" }
    };
    return roles;
}

int TimezoneModelRegion::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_timezoneRegions.count();
}

QVariant TimezoneModelRegion::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= m_timezoneRegions.count())
        return QVariant();

    const Region &region = m_timezoneRegions.at(row);

    switch(role) {
    case RegionRole:
        return region.m_region;
    case RegionRoleTranslated:
        return m_translations->translate(region.m_region);
    }
    return QVariant();
}

void TimezoneModelRegion::fillModel()
{
    const QStringList& timezones = m_timezoneController->getTimezones();
    beginResetModel();
    m_timezoneRegions.clear();
    for (const QString &timezone : timezones) {
        QString region = TimezoneExtractor::extractRegion(timezone);;
        if(isNewRegion(region)) {
            Region regionAdd {
                region
            };
            m_timezoneRegions.append(regionAdd);
        }
    }
    endResetModel();
}

bool TimezoneModelRegion::isNewRegion(const QString &region) const
{
    for (const Region &regionAvail : m_timezoneRegions)
        if(regionAvail.m_region == region)
            return false;
    return true;
}
