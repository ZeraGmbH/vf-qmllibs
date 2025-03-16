#include "timezonestatecontroller.h"
#include "timezoneextractor.h"
#include "timezonetranslations.h"

TimezoneStateController::TimezoneStateController(AbstractTimedate1ConnectionPtr timedateConnection) :
    m_timedateConnection(timedateConnection)
{
    fillTimezones();
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged,
            this, &TimezoneStateController::fillTimezones);
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigTimezoneChanged,
            this, &TimezoneStateController::setSystemTimezone);
    connect(this, &TimezoneStateController::sigCityChanged,
            this, &TimezoneStateController::handleCityChange);
}

const QStringList &TimezoneStateController::getTimezones() const
{
    return m_timezones;
}

QString TimezoneStateController::getSelectedRegion() const
{
    return m_selectedRegion;
}

void TimezoneStateController::setSelectedRegion(const QString &region)
{
    if (m_selectedRegion != region && isValidRegion(region)) {
        changeRegion(region);
        if(!m_selectedCity.isEmpty())
            changeCity("");
    }
}

QString TimezoneStateController::getSelectedCity() const
{
    return m_selectedCity;
}

void TimezoneStateController::setSelectedCity(const QString &city)
{
    if (m_selectedCity != city && isValidCity(city))
        changeCity(city);
}

bool TimezoneStateController::canUndo() const
{
    return m_canUndo;
}

void TimezoneStateController::doUndo()
{
    setSystemTimezone();
}

bool TimezoneStateController::canApply() const
{
    return m_canApply;
}

void TimezoneStateController::doApply()
{
    const QString timezone =
        m_selectedRegion == TimezoneTranslations::noRegionString() ?
                                 m_selectedCity : QString("%1/%2").arg(m_selectedRegion, m_selectedCity);
    m_timedateConnection->setTimezone(timezone);
}

void TimezoneStateController::fillTimezones()
{
    const QStringList& newTimezones = m_timedateConnection->getAvailTimezones();
    if (m_timezones != newTimezones) {
        m_timezones = newTimezones;
        emit sigTimezonesChanged();
        const QString newTimezone = m_timedateConnection->getTimeszone();
        setSelectedRegion(TimezoneExtractor::extractRegion(newTimezone));
        setSelectedCity(TimezoneExtractor::extractCity(newTimezone));
    }
}

void TimezoneStateController::handleCityChange()
{
    const QString timezone = m_timedateConnection->getTimeszone();
    const QString currentRegion = TimezoneExtractor::extractRegion(timezone);
    const QString currentCity = TimezoneExtractor::extractCity(timezone);

    bool newCanUndo = m_selectedRegion != currentRegion || m_selectedCity != currentCity;
    if (m_canUndo != newCanUndo) {
        m_canUndo = newCanUndo;
        emit sigCanUndoChanged();
    }

    bool newCanApply = !m_selectedCity.isEmpty() && m_selectedCity != currentCity;
    if (m_canApply != newCanApply) {
        m_canApply = newCanApply;
        emit sigCanApplyChanged();
    }
}

void TimezoneStateController::setSystemTimezone()
{
    bool oldCanUndo = m_canUndo; // avoid on city change emit of sigCanUndoChanged
    m_canUndo = false;
    bool oldCanApply = m_canApply; // avoid on city change emit of sigCanApplyChanged
    m_canApply = false;

    QString timezone = m_timedateConnection->getTimeszone();

    QString region = TimezoneExtractor::extractRegion(timezone);
    if (m_selectedRegion != region)
        changeRegion(region);
    QString city = TimezoneExtractor::extractCity(timezone);
    if (m_selectedCity != city)
        changeCity(city);

    if (oldCanUndo)
        emit sigCanUndoChanged();
    if (oldCanApply)
        emit sigCanApplyChanged();
}

bool TimezoneStateController::isValidRegion(const QString &region) const
{
    for (const QString &timezone : m_timezones)
        if (region == TimezoneExtractor::extractRegion(timezone))
            return true;
    return false;
}

void TimezoneStateController::changeRegion(const QString &region)
{
    m_selectedRegion = region;
    emit sigRegionChanged();
}

bool TimezoneStateController::isValidCity(const QString &city) const
{
    for (const QString &timezone : m_timezones)
        if (m_selectedRegion == TimezoneExtractor::extractRegion(timezone))
            if (city == TimezoneExtractor::extractCity(timezone))
                return true;
    return false;
}

void TimezoneStateController::changeCity(const QString &city)
{
    m_selectedCity = city;
    emit sigCityChanged();
}
