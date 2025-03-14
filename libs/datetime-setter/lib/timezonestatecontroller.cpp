#include "timezonestatecontroller.h"
#include "timezoneextractor.h"

TimezoneStateController::TimezoneStateController(std::shared_ptr<AbstractTimedate1Connection> timedateConnection) :
    m_timedateConnection{timedateConnection}
{
    fillTimezones();
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged,
            this, &TimezoneStateController::fillTimezones);
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
        m_selectedRegion = region;
        emit sigRegionChanged();
        if(!m_selectedCity.isEmpty()) {
            m_selectedCity.clear();
            emit sigCityChanged();
        }
    }
}

QString TimezoneStateController::getSelectedCity() const
{
    return m_selectedCity;
}

void TimezoneStateController::setSelectedCity(const QString &city)
{
    if (m_selectedCity != city && isValidCity(city)) {
        m_selectedCity = city;
        emit sigCityChanged();
    }
}

bool TimezoneStateController::canApply() const
{
    return m_canApply;
}

void TimezoneStateController::doApply()
{

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
    const QString currentCity = TimezoneExtractor::extractCity(m_timedateConnection->getTimeszone());
    bool newCanApply = !m_selectedCity.isEmpty() && m_selectedCity != currentCity;
    if (m_canApply != newCanApply) {
        m_canApply = newCanApply;
        emit sigCanApplyChanged();
    }
}

bool TimezoneStateController::isValidRegion(const QString &region) const
{
    for (const QString &timezone : m_timezones)
        if (region == TimezoneExtractor::extractRegion(timezone))
            return true;
    return false;
}

bool TimezoneStateController::isValidCity(const QString &city) const
{
    for (const QString &timezone : m_timezones)
        if (m_selectedRegion == TimezoneExtractor::extractRegion(timezone))
            if (city == TimezoneExtractor::extractCity(timezone))
                return true;
    return false;
}
