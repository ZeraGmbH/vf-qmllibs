#ifndef TIMEZONEMODELFILTERED_H
#define TIMEZONEMODELFILTERED_H

#include "timezonemodelbase.h"

class TimezoneModelFiltered : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneModelFiltered(std::shared_ptr<TimezoneModelBase> sourceModel);
    Q_INVOKABLE void setRegion(const QString &region);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    enum Roles {
        TimezoneRole = Qt::UserRole,
        CityOrCountryRoleTranslated
    };

private slots:
    void fillModel();

private:
    std::shared_ptr<QAbstractListModel> m_sourceModel;
    QString m_region;
    struct Timezone {
        QString m_timezone;
        QString m_cityTranslated;
    };
    QList<Timezone> m_timezoneFilteredSorted;
};

#endif // TIMEZONEMODELFILTERED_H
