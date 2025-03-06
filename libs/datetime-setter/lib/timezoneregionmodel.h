#ifndef TIMEZONEREGIONMODEL_H
#define TIMEZONEREGIONMODEL_H

#include "timezonebasemodel.h"

class TimezoneRegionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneRegionModel(std::shared_ptr<TimezoneBaseModel> sourceModel);
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

    std::shared_ptr<TimezoneBaseModel> m_sourceModel;
    struct Region {
        QString m_region;
        QString m_regionTranslated;
    };
    QList<Region> m_timezoneRegions;
};

#endif // TIMEZONEREGIONMODEL_H
