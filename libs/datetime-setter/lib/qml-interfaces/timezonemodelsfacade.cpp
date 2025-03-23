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
    connect(m_timezoneController.get(), &TimezoneStateController::sigSelectedTimezoneChanged,
            this, &TimezoneModelsFacade::sigSelectedTimezoneChanged);
    connect(m_timezoneController.get(), &TimezoneStateController::sigCanApplyChanged,
            this, &TimezoneModelsFacade::sigCanApplyChangesChanged);

    connect(ZeraTranslation::getInstance(), &ZeraTranslation::sigLanguageChanged,
            this, &TimezoneModelsFacade::handleLanguageChange);
}

QAbstractListModel *TimezoneModelsFacade::getRegionModel() const
{
    return m_modelRegion.get();
}

QAbstractListModel *TimezoneModelsFacade::getCityModel() const
{
    return m_modelCities.get();
}

QString TimezoneModelsFacade::getSelectedTimezone() const
{
    return m_timezoneController->getSelectedTimezone();
}

void TimezoneModelsFacade::doUndoChanges()
{
    m_timezoneController->doUndo();
}

bool TimezoneModelsFacade::canApplyChanges() const
{
    return m_timezoneController->canApply();
}

void TimezoneModelsFacade::handleLanguageChange()
{
    m_translations->setLanguage(ZeraTranslation::getInstance()->getLanguage());
}
