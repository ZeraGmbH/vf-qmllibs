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

    Q_PROPERTY(QString regionSelected READ getRegionSelected WRITE setRegionSelected NOTIFY sigRegionSelectedChanged FINAL)
    QString getRegionSelected() const;
    void setRegionSelected(const QString &region);

    Q_PROPERTY(QAbstractListModel* cityModel READ getCityModel CONSTANT)
    QAbstractListModel* getCityModel() const;

    Q_PROPERTY(QString citySelected READ getCitySelected WRITE setCitySelected NOTIFY sigCitySelectedChanged FINAL)
    QString getCitySelected() const;
    void setCitySelected(const QString &city);

    // convenience helper
    Q_INVOKABLE int maxDaysInYearMonth(int year, int month);

    Q_PROPERTY(bool canUndo READ canUndo NOTIFY sigCanUndoChanged FINAL)
    bool canUndo() const;
    Q_INVOKABLE void doUndo();

    Q_PROPERTY(bool canApply READ canApply NOTIFY sigCanApplyChanged FINAL)
    bool canApply() const;
    Q_INVOKABLE void doApply();

signals:
    void sigRegionSelectedChanged();
    void sigCitySelectedChanged();
    void sigCanUndoChanged();
    void sigCanApplyChanged();

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
