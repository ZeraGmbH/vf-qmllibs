#ifndef TIMEZONEMODELCITYFILTERED_H
#define TIMEZONEMODELCITYFILTERED_H

#include "timezonestatecontroller.h"
#include "timezonetranslations.h"
#include <QAbstractListModel>

class TimezoneModelCityFiltered : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneModelCityFiltered(TimezoneStateControllerPtr timezoneController,
                                       TimezoneTranslationsPtr translations);

    enum Roles {
        TimezoneRole = Qt::UserRole,
        CityRoleTranslated
    };
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_PROPERTY(int selectedIndex READ getSelectedIndex WRITE setSelectedIndex NOTIFY sigSelectedIndexChanged FINAL)
    int getSelectedIndex() const;
    void setSelectedIndex(int index);
    Q_SIGNAL void sigSelectedIndexChanged();

private slots:
    void fillModel();
    void handleCityChange();
private:
    int findSelectedCity() const;
    TimezoneStateControllerPtr m_timezoneController;
    TimezoneTranslationsPtr m_translations;
    struct City {
        QString m_timezone;
        QString m_city;
        QString m_cityTranslated;
    };
    QList<City> m_citiesSorted;
    int m_selectedIndex = -1;
};

#endif // TIMEZONEMODELCITYFILTERED_H
