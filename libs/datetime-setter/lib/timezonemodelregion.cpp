#include "timezonemodelregion.h"
#include "timezoneextractor.h"
#include <QMap>
#include <QSet>

TimezoneModelRegion::TimezoneModelRegion(std::shared_ptr<TimezoneStateController> timezoneController,
                                         std::shared_ptr<TimezoneTranslations> translations) :
    m_timezoneController(timezoneController),
    m_translations(translations)
{
    fillModel();
    connect(m_timezoneController.get(), &TimezoneStateController::sigTimezonesChanged,
            this, &TimezoneModelRegion::fillModel);
    connect(m_timezoneController.get(), &TimezoneStateController::sigRegionChanged,
            this, &TimezoneModelRegion::handleRegionChanged);
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
        return region.m_regionTr;
    }
    return QVariant();
}

int TimezoneModelRegion::getSelectedIndex() const
{
    return m_selectedIndex;
}

void TimezoneModelRegion::setSelectedIndex(int index)
{
    if (index < 0 || index >= m_timezoneRegions.count()) {
        qWarning("TimezoneModelRegion::setSelectedIndex out of limit: %i!", index);
        return;
    }
    if (m_selectedIndex != index) {
        const QString &newRegion = m_timezoneRegions[index].m_region;
        m_timezoneController->setSelectedRegion(newRegion);
    }
}

void TimezoneModelRegion::fillModel()
{
    const QStringList& timezones = m_timezoneController->getTimezones();
    QMap<QString /*regionTr*/, QString/*region*/> sortedRegions;
    QSet<QString> addedRegions;
    bool noRegionFound = false;
    for (const QString &timezone : timezones) {
        QString region = TimezoneExtractor::extractRegion(timezone);;
        if (!addedRegions.contains(region)) {
            addedRegions.insert(region);
            if(region != TimezoneTranslations::noRegionString())
                sortedRegions[m_translations->translate(region)] = region;
            else
                noRegionFound = true;
        }
    }

    beginResetModel();
    m_timezoneRegions.clear();
    for (auto iter=sortedRegions.constBegin(); iter!=sortedRegions.constEnd(); ++iter)
        m_timezoneRegions.append({iter.value(), iter.key()});
    if (noRegionFound) {
        const QString noRegionString = TimezoneTranslations::noRegionString();
        m_timezoneRegions.append({ noRegionString, m_translations->translate(noRegionString) });
    }
    endResetModel();
    handleRegionChanged();
}

void TimezoneModelRegion::handleRegionChanged()
{
    int newIndex = findSelectedIndex();
    if (m_selectedIndex != newIndex) {
        m_selectedIndex = newIndex;
        emit sigSelectedIndexChanged();
    }
}

int TimezoneModelRegion::findSelectedIndex() const
{
    const QString currentRegion = m_timezoneController->getSelectedRegion();
    for (int i=0; i<m_timezoneRegions.count(); i++) {
        const Region &region = m_timezoneRegions[i];
        if (region.m_region == currentRegion)
            return i;
    }
    return -1;
}
