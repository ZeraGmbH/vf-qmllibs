#ifndef TIMEZONEBASEMODEL_H
#define TIMEZONEBASEMODEL_H

#include "abstracttimedate1connection.h"
#include "timezonetranslations.h"
#include <QAbstractListModel>
#include <QList>
#include <memory>

class TimezoneBaseModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneBaseModel(std::shared_ptr<AbstractTimedate1Connection> timedateConnection,
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
    void setLanguage(const QString &language);

private slots:
    void fillModel();
private:
    QStringList m_timezones;
    std::shared_ptr<AbstractTimedate1Connection> m_timedateConnection;
    std::shared_ptr<TimezoneTranslations> m_translations;
};

#endif // TIMEZONEBASEMODEL_H
