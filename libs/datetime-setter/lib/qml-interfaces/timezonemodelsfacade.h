#ifndef TIMEZONEMODELSFACADE_H
#define TIMEZONEMODELSFACADE_H

#include "abstracttimedate1connection.h"
#include "timezonestatecontroller.h"
#include "timezonemodelcityfiltered.h"
#include "timezonemodelregion.h"
#include "timezonetranslations.h"
#include <QAbstractListModel>

class TimezoneModelsFacade : public QObject
{
    Q_OBJECT
public:
    explicit TimezoneModelsFacade();
    explicit TimezoneModelsFacade(AbstractTimedate1ConnectionPtr timedateConnection,
                                  TimezoneTranslationsPtr translations);

    Q_PROPERTY(QAbstractListModel* regionModel READ getRegionModel CONSTANT)
    QAbstractListModel* getRegionModel() const;

    Q_PROPERTY(QAbstractListModel* cityModel READ getCityModel CONSTANT)
    QAbstractListModel* getCityModel() const;

    Q_PROPERTY(QString selectedTimezone READ getSelectedTimezone NOTIFY sigSelectedTimezoneChanged FINAL)
    QString getSelectedTimezone() const;
    Q_SIGNAL void sigSelectedTimezoneChanged();

    Q_INVOKABLE void doUndoChanges();

    Q_PROPERTY(bool canApplyChanges READ canApplyChanges NOTIFY sigCanApplyChangesChanged FINAL)
    bool canApplyChanges() const;
    Q_SIGNAL void sigCanApplyChangesChanged();

private slots:
    void handleLanguageChange();
private:
    AbstractTimedate1ConnectionPtr m_timedateConnection;
    TimezoneTranslationsPtr m_translations;
    TimezoneStateControllerPtr m_timezoneController;
    std::shared_ptr<TimezoneModelRegion> m_modelRegion;
    std::shared_ptr<TimezoneModelCityFiltered> m_modelCities;
};

#endif // TIMEZONEMODELSFACADE_H
