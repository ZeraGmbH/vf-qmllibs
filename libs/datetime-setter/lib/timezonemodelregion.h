#ifndef TIMEZONEMODELREGION_H
#define TIMEZONEMODELREGION_H

#include "timezonestatecontroller.h"
#include "timezonetranslations.h"
#include <QAbstractListModel>

class TimezoneModelRegion : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneModelRegion(TimezoneStateControllerPtr timezoneController,
                                 TimezoneTranslationsPtr translations);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    enum Roles {
        RegionRole = Qt::UserRole,
        RegionRoleTranslated
    };
    Q_PROPERTY(int selectedIndex READ getSelectedIndex WRITE setSelectedIndex NOTIFY sigSelectedIndexChanged FINAL)
    int getSelectedIndex() const;
    void setSelectedIndex(int index);
signals:
    void sigSelectedIndexChanged();

private slots:
    void fillModel();
    void handleRegionChanged();
private:
    int findSelectedIndex() const;
    TimezoneStateControllerPtr m_timezoneController;
    TimezoneTranslationsPtr m_translations;
    struct Region {
        QString m_region;
        QString m_regionTr;
    };
    QList<Region> m_timezoneRegions;
    int m_selectedIndex = -1;
};

#endif // TIMEZONEMODELREGION_H
