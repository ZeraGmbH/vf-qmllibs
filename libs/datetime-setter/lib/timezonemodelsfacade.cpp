#include "timezonemodelsfacade.h"

TimezoneModelsFacade::TimezoneModelsFacade(std::shared_ptr<AbstractTimedate1Connection> timedateConnection,
                                           std::shared_ptr<TimezoneTranslations> translations) :
    m_timedateConnection(timedateConnection),
    m_translations(translations),
    m_modelBase(std::make_shared<TimezoneModelBase>(m_timedateConnection, m_translations)),
    m_modelRegion(std::make_shared<TimezoneModelRegion>(m_modelBase)),
    m_modelCities(std::make_shared<TimezoneModelCityFiltered>(m_modelBase))
{
    connect(m_modelBase.get(), &TimezoneModelBase::sigRegionChanged,
            this, &TimezoneModelsFacade::sigRegionSelectedChanged);
    connect(m_modelBase.get(), &TimezoneModelBase::sigCityChanged,
            this, &TimezoneModelsFacade::sigCitySelectedChanged);
}

QAbstractListModel *TimezoneModelsFacade::getRegionModel() const
{
    return m_modelRegion.get();
}

QString TimezoneModelsFacade::getRegionSelected() const
{
    return m_modelBase->getSelectedRegion();
}

void TimezoneModelsFacade::setRegionSelected(const QString &region)
{
    m_modelBase->setSelectedRegion(region);
}

QAbstractListModel *TimezoneModelsFacade::getCityModel() const
{
    return m_modelCities.get();
}

QString TimezoneModelsFacade::getCitySelected() const
{
    return m_modelBase->getSelectedCity();
}

void TimezoneModelsFacade::setCitySelected(const QString &city)
{
    m_modelBase->setSelectedCity(city);
}

bool TimezoneModelsFacade::canApply() const
{

}

void TimezoneModelsFacade::doApply()
{

}
