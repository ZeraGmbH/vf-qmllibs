#ifndef TIMEZONESTATECONTROLLER_H
#define TIMEZONESTATECONTROLLER_H

#include "abstracttimedate1connection.h"
#include <memory>

class TimezoneStateController : public QObject
{
    Q_OBJECT
public:
    explicit TimezoneStateController(std::shared_ptr<AbstractTimedate1Connection> timedateConnection);

    const QStringList &getTimezones() const;

    QString getSelectedRegion() const;
    void setSelectedRegion(const QString &region);

    QString getSelectedCity() const;
    void setSelectedCity(const QString &city);

    // In case of future extensions/changes we should think about separating Undo/Apply
    // out into another class. Implementation and Tests are already big and complex...
    bool canUndo() const;
    void doUndo();
    bool canApply() const;
    void doApply();

signals:
    void sigTimezonesChanged();
    void sigRegionChanged();
    void sigCityChanged();
    void sigCanUndoChanged();
    void sigCanApplyChanged();

private slots:
    void fillTimezones();
    void handleCityChange();
    void setSystemTimezone();
private:
    bool isValidRegion(const QString &region) const;
    void changeRegion(const QString &region);
    bool isValidCity(const QString &city) const;
    void changeCity(const QString &city);

    QStringList m_timezones;
    std::shared_ptr<AbstractTimedate1Connection> m_timedateConnection;

    QString m_selectedRegion;
    QString m_selectedCity;
    bool m_canUndo = false;
    bool m_canApply = false;
};

#endif // TIMEZONESTATECONTROLLER_H
