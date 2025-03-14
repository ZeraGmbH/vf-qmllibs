#include "timezonemodelsfacade.h"
#include "timedate1connection.h"
#include <zeratranslation.h>

TimezoneModelsFacade::TimezoneModelsFacade() :
    TimezoneModelsFacade(std::make_shared<Timedate1Connection>(), std::make_shared<TimezoneTranslations>())
{
    m_timedateConnection->start();
}

TimezoneModelsFacade::TimezoneModelsFacade(std::shared_ptr<AbstractTimedate1Connection> timedateConnection,
                                           std::shared_ptr<TimezoneTranslations> translations) :
    m_timedateConnection(timedateConnection),
    m_translations(translations),
    m_timezoneController(std::make_shared<TimezoneStateController>(m_timedateConnection)),
    m_modelRegion(std::make_shared<TimezoneModelRegion>(m_timezoneController, m_translations)),
    m_modelCities(std::make_shared<TimezoneModelCityFiltered>(m_timezoneController, m_translations))
{
    connect(m_timezoneController.get(), &TimezoneStateController::sigRegionChanged,
            this, &TimezoneModelsFacade::sigRegionSelectedChanged);
    connect(m_timezoneController.get(), &TimezoneStateController::sigCityChanged,
            this, &TimezoneModelsFacade::sigCitySelectedChanged);
    connect(m_timezoneController.get(), &TimezoneStateController::sigCanApplyChanged,
            this, &TimezoneModelsFacade::sigCanApplyChanged);
    connect(ZeraTranslation::getInstance(), &ZeraTranslation::sigLanguageChanged,
            this, &TimezoneModelsFacade::onLanguageChanged);
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

bool TimezoneModelsFacade::canApply() const
{
    return m_timezoneController->canApply();
}

void TimezoneModelsFacade::doApply()
{
    m_timezoneController->doApply();
}

void TimezoneModelsFacade::onLanguageChanged()
{
    m_translations->setLanguage(ZeraTranslation::getInstance()->getLanguage());
}
