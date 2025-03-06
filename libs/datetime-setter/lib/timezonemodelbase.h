#ifndef TIMEZONEMODELBASE_H
#define TIMEZONEMODELBASE_H

#include "abstracttimedate1connection.h"
#include "timezonetranslations.h"
#include <QAbstractListModel>
#include <QStringList>
#include <memory>

class TimezoneModelBase : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneModelBase(std::shared_ptr<AbstractTimedate1Connection> timedateConnection,
                               std::shared_ptr<TimezoneTranslations> translations);
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    enum Roles {
        TimezoneRole = Qt::UserRole,
        TimezoneRoleTranslated,
        RegionRole,
        RegionRoleTranslated,
        CityOrCountryRole,
        CityOrCountryRoleTranslated
    };

private slots:
    void fillModel();
private:
    QStringList m_timezones;
    std::shared_ptr<AbstractTimedate1Connection> m_timedateConnection;
    std::shared_ptr<TimezoneTranslations> m_translations;
};

#endif // TIMEZONEMODELBASE_H
