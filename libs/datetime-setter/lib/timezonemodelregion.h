#ifndef TIMEZONEMODELREGION_H
#define TIMEZONEMODELREGION_H

#include "timezonestatecontroller.h"
#include "timezonetranslations.h"
#include <QAbstractListModel>

class TimezoneModelRegion : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneModelRegion(std::shared_ptr<TimezoneStateController> timezoneController,
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
    std::shared_ptr<TimezoneStateController> m_timezoneController;
    std::shared_ptr<TimezoneTranslations> m_translations;
    struct Region {
        QString m_region;
        QString m_regionTr;
    };
    QList<Region> m_timezoneRegions;
};

#endif // TIMEZONEMODELREGION_H
