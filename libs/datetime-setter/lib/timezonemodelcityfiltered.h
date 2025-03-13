#ifndef TIMEZONEMODELCITYFILTERED_H
#define TIMEZONEMODELCITYFILTERED_H

#include "timezonestatecontroller.h"
#include "timezonetranslations.h"
#include <QAbstractListModel>

class TimezoneModelCityFiltered : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneModelCityFiltered(std::shared_ptr<TimezoneStateController> timezoneController,
                                       std::shared_ptr<TimezoneTranslations> translations);
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
    std::shared_ptr<TimezoneStateController> m_timezoneController;
    std::shared_ptr<TimezoneTranslations> m_translations;
    QString m_region;
    struct Timezone {
        QString m_timezone;
        QString m_cityTranslated;
    };
    QList<Timezone> m_timezoneFilteredSorted;
};

#endif // TIMEZONEMODELCITYFILTERED_H
