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
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    enum Roles {
        TimezoneRole = Qt::UserRole,
        CityRoleTranslated
    };
    Q_PROPERTY(int selectedIndex READ getSelectedIndex WRITE setSelectedIndex NOTIFY sigSelectedIndexChanged FINAL)
    int getSelectedIndex() const;
    void setSelectedIndex(int index);
signals:
    void sigSelectedIndexChanged();

private slots:
    void fillModel();
    void handleCityChange();
private:
    int findSelectedCity() const;
    std::shared_ptr<TimezoneStateController> m_timezoneController;
    std::shared_ptr<TimezoneTranslations> m_translations;
    struct City {
        QString m_timezone;
        QString m_city;
        QString m_cityTranslated;
    };
    QList<City> m_citiesSorted;
    int m_selectedIndex = -1;
};

#endif // TIMEZONEMODELCITYFILTERED_H
