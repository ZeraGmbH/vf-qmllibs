#ifndef TIMEZONEMODELSFACADE_H
#define TIMEZONEMODELSFACADE_H

#include "abstracttimedate1connection.h"
#include "timezonestatecontroller.h"
#include "timezonemodelcityfiltered.h"
#include "timezonemodelregion.h"
#include "timezonetranslations.h"
#include <QAbstractListModel>
#include <memory>

class TimezoneModelsFacade : public QObject
{
    Q_OBJECT
public:
    explicit TimezoneModelsFacade();
    explicit TimezoneModelsFacade(std::shared_ptr<AbstractTimedate1Connection> timedateConnection,
                                  std::shared_ptr<TimezoneTranslations> translations);

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
    std::shared_ptr<AbstractTimedate1Connection> m_timedateConnection;
    std::shared_ptr<TimezoneTranslations> m_translations;
    std::shared_ptr<TimezoneStateController> m_timezoneController;
    std::shared_ptr<TimezoneModelRegion> m_modelRegion;
    std::shared_ptr<TimezoneModelCityFiltered> m_modelCities;
};

#endif // TIMEZONEMODELSFACADE_H
