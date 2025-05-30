#ifndef TIMEZONESTATECONTROLLER_H
#define TIMEZONESTATECONTROLLER_H

#include "abstracttimedate1connection.h"

class TimezoneStateController : public QObject
{
    Q_OBJECT
public:
    explicit TimezoneStateController(AbstractTimedate1ConnectionPtr timedateConnection);

    const QStringList &getTimezones() const;
    Q_SIGNAL void sigTimezonesChanged();

    QString getSelectedRegion() const;
    void setSelectedRegion(const QString &region);
    Q_SIGNAL void sigRegionChanged();

    QString getSelectedCity() const;
    void setSelectedCity(const QString &city);
    Q_SIGNAL void sigCityChanged();

    QString getSelectedTimezone() const;
    Q_SIGNAL void sigSelectedTimezoneChanged();

    bool canUndo() const;
    void doUndo();
    Q_SIGNAL void sigCanUndoChanged();

    // We have tasks to change setting -> no doApply
    bool canApply() const;
    Q_SIGNAL void sigCanApplyChanged();

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
    AbstractTimedate1ConnectionPtr m_timedateConnection;

    QString m_selectedRegion;
    QString m_selectedCity;
    bool m_canUndo = false;
    bool m_canApply = false;
};

typedef std::shared_ptr<TimezoneStateController> TimezoneStateControllerPtr;

#endif // TIMEZONESTATECONTROLLER_H
