#ifndef TIMEZONEMODELREGION_H
#define TIMEZONEMODELREGION_H

#include "timezonemodelbase.h"

class TimezoneModelRegion : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneModelRegion(std::shared_ptr<TimezoneModelBase> sourceModel);
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    enum Roles {
        RegionRole = Qt::UserRole,
        RegionRoleTranslated
    };

private slots:
    void fillModel();
private:
    void tryAddRegion(int regionNum);

    std::shared_ptr<TimezoneModelBase> m_sourceModel;
    struct Region {
        QString m_region;
        QString m_regionTranslated;
    };
    QList<Region> m_timezoneRegions;
};

#endif // TIMEZONEMODELREGION_H
