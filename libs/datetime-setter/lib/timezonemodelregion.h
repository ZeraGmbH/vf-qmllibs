#ifndef TIMEZONEMODELREGION_H
#define TIMEZONEMODELREGION_H

#include "timezonemodelbase.h"
#include "timezonetranslations.h"

class TimezoneModelRegion : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneModelRegion(std::shared_ptr<TimezoneModelBase> sourceModel,
                                 std::shared_ptr<TimezoneTranslations> translations);

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
    bool isNewRegion(const QString &region) const;

    std::shared_ptr<TimezoneModelBase> m_sourceModel;
    std::shared_ptr<TimezoneTranslations> m_translations;
    struct Region {
        QString m_region;
    };
    QList<Region> m_timezoneRegions;
};

#endif // TIMEZONEMODELREGION_H
