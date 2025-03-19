#include "timezonemodelsfacade.h"
#include "timedate1connection.h"
#include <zeratranslation.h>

TimezoneModelsFacade::TimezoneModelsFacade() :
    TimezoneModelsFacade(std::make_shared<Timedate1Connection>(), std::make_shared<TimezoneTranslations>())
{
    m_timedateConnection->start();
}

TimezoneModelsFacade::TimezoneModelsFacade(AbstractTimedate1ConnectionPtr timedateConnection,
                                           TimezoneTranslationsPtr translations) :
    m_timedateConnection(timedateConnection),
    m_translations(translations),
    m_timezoneController(std::make_shared<TimezoneStateController>(m_timedateConnection)),
    m_modelRegion(std::make_shared<TimezoneModelRegion>(m_timezoneController, m_translations)),
    m_modelCities(std::make_shared<TimezoneModelCityFiltered>(m_timezoneController, m_translations))
{
    handleLanguageChange();
    connect(m_timezoneController.get(), &TimezoneStateController::sigRegionChanged,
            this, &TimezoneModelsFacade::sigRegionSelectedChanged);
    connect(m_timezoneController.get(), &TimezoneStateController::sigCityChanged,
            this, &TimezoneModelsFacade::sigCitySelectedChanged);
    connect(m_timezoneController.get(), &TimezoneStateController::sigCanUndoChanged,
            this, &TimezoneModelsFacade::sigCanUndoChanged);
    connect(m_timezoneController.get(), &TimezoneStateController::sigCanApplyChanged,
            this, &TimezoneModelsFacade::sigCanApplyChanged);
    connect(ZeraTranslation::getInstance(), &ZeraTranslation::sigLanguageChanged,
            this, &TimezoneModelsFacade::handleLanguageChange);
}

QAbstractListModel *TimezoneModelsFacade::getRegionModel() const
{
    return m_modelRegion.get();
}

QString TimezoneModelsFacade::getRegionSelected() const
{
    return m_timezoneController->getSelectedRegion();
}

void TimezoneModelsFacade::setRegionSelected(const QString &region)
{
    m_timezoneController->setSelectedRegion(region);
}

QAbstractListModel *TimezoneModelsFacade::getCityModel() const
{
    return m_modelCities.get();
}

QString TimezoneModelsFacade::getCitySelected() const
{
    return m_timezoneController->getSelectedCity();
}

void TimezoneModelsFacade::setCitySelected(const QString &city)
{
    m_timezoneController->setSelectedCity(city);
}

int TimezoneModelsFacade::maxDaysInYearMonth(int year, int month)
{
    QCalendar calendar;
    return calendar.daysInMonth(month, year);
}

bool TimezoneModelsFacade::canUndo() const
{
    return m_timezoneController->canUndo();
}

void TimezoneModelsFacade::doUndo()
{
    m_timezoneController->doUndo();
}

bool TimezoneModelsFacade::canApply() const
{
    return m_timezoneController->canApply();
}

void TimezoneModelsFacade::doApply()
{
    m_timezoneController->doApply();
}

void TimezoneModelsFacade::handleLanguageChange()
{
    m_translations->setLanguage(ZeraTranslation::getInstance()->getLanguage());
}
