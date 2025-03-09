#include "timezonemodelregion.h"

TimezoneModelRegion::TimezoneModelRegion(std::shared_ptr<TimezoneModelBase> sourceModel) :
    m_sourceModel(sourceModel)
{
    fillModel();
    connect(m_sourceModel.get(), &QAbstractItemModel::modelReset,
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
        return region.m_regionTranslated;
    }
    return QVariant();
}

void TimezoneModelRegion::fillModel()
{
    int timezoneCount = m_sourceModel->rowCount();
    beginResetModel();
    m_timezoneRegions.clear();
    for (int i=0; i<timezoneCount; ++i) {
        QModelIndex index = m_sourceModel->index(i, 0);
        QString regionStr = m_sourceModel->data(index, TimezoneModelBase::RegionRole).toString();
        if(isNewRegion(regionStr)) {
            Region regionAdd {
                regionStr,
                m_sourceModel->data(index, TimezoneModelBase::RegionRoleTranslated).toString()
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
