#ifndef TIMEZONEMODELBASE_H
#define TIMEZONEMODELBASE_H

#include "abstracttimedate1connection.h"
#include <QAbstractListModel>
#include <QStringList>
#include <memory>

class TimezoneModelBase : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneModelBase(std::shared_ptr<AbstractTimedate1Connection> timedateConnection);

    QString getSelectedRegion() const;
    void setSelectedRegion(const QString &region);

    QString getSelectedCity() const;
    void setSelectedCity(const QString &city);

    bool canApply() const;
    void doApply();

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    enum Roles {
        TimezoneRole = Qt::UserRole,
        RegionRole,
        CityOrCountryRole
    };
signals:
    void sigRegionChanged();
    void sigCityChanged();
    void sigCanApplyChanged();

private slots:
    void fillModelSetDefaultsFromDateTime();
    void fillModel();
    void handleCityChange();
private:
    QString regionFromTimezone(const QString &timezone) const;
    QString cityFromTimezone(const QString &timezone) const;
    bool isValidRegion(const QString &region) const;
    bool isValidCity(const QString &city) const;

    QStringList m_timezones;
    std::shared_ptr<AbstractTimedate1Connection> m_timedateConnection;

    QString m_selectedRegion;
    QString m_selectedCity;
    bool m_canApply = false;
};

#endif // TIMEZONEMODELBASE_H
