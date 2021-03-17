#include "abstractconnectionsettingsinterface.h"

AbstractConnectionSettingsInterface::AbstractConnectionSettingsInterface(QObject* parent) : QObject(parent)
{
    m_connection = NULL;
}

void AbstractConnectionSettingsInterface::load(QString p_path)
{
    m_connection = NetworkManager::findConnection(p_path);
    if(m_connection != NULL){
        m_settings = m_connection->settings();
        m_connectionMap = m_connection->settings()->toMap();
        QString iname = m_settings->interfaceName();
        //m_settings->setAutoconnect(false);
        emit loadComplete();
    }else{
        create();
    }

}

void AbstractConnectionSettingsInterface::create()
{
    m_settings= NetworkManager::ConnectionSettings::Ptr::create(NetworkManager::ConnectionSettings::ConnectionType::Unknown);
}

void AbstractConnectionSettingsInterface::save()
{
    NMVariantMapMap map = m_settings->toMap();
    if(map.contains("connection")){

        if(map["connection"].contains("interface-name")){
            map["connection"].remove("interface-name");
        }

        if(map.contains("802-11-wireless")){
            if(map["802-11-wireless"].contains("mac-address")){
                map["802-11-wireless"].remove("mac-address");
            }
        }
    }

    if(m_settings->setting(NetworkManager::Setting::SettingType::Ipv4).staticCast<NetworkManager::Ipv4Setting>()->method() == NetworkManager::Ipv4Setting::ConfigMethod::Automatic){
        if(map.contains("ipv4")){
            if(map["ipv4"].contains("addresses")){
                map["ipv4"].remove("addresses");
            }
            if(map["ipv4"].contains("address-data")){
                map["ipv4"].remove("address-data");
            }
        }
    }

    if(m_settings->setting(NetworkManager::Setting::SettingType::Ipv6).staticCast<NetworkManager::Ipv6Setting>()->method() == NetworkManager::Ipv6Setting::ConfigMethod::Automatic){
        if(map.contains("ipv6")){
            if(map["ipv6"].contains("addresses")){
                map["ipv6"].remove("addresses");
            }
            if(map["ipv6"].contains("address-data")){
                map["ipv6"].remove("address-data");
            }
        }
    }


    if(m_connection != NULL){

        m_connection->update(map);
    }else{
        NetworkManager::addConnection(map);
        m_settings.clear();
    }
}

void AbstractConnectionSettingsInterface::saveAndActivate(const QString &p_devUni,const QString &p_apPath)
{
    if(m_connection == NULL){
        NMVariantMapMap map = m_settings->toMap();
        NetworkManager::addAndActivateConnection(map,p_devUni,"");
        m_settings.clear();
    }
}

void AbstractConnectionSettingsInterface::discard()
{
    if(m_connection != NULL){
        m_connection->updateUnsaved(m_connectionMap);
    }else{
        NMVariantMapMap map = m_settings->toMap();
        m_settings.clear();
    }
}

QStringList AbstractConnectionSettingsInterface::getDevices()
{
    return QStringList();
}

QString AbstractConnectionSettingsInterface::getDevicePath(const QString &p_interfaceName)
{
    return QString();
}

QString AbstractConnectionSettingsInterface::getDevice()
{
    if(m_connection != NULL){
        return m_settings->interfaceName();
    }else{
        return "";
    }
}

void AbstractConnectionSettingsInterface::setDevice(QString &device)
{
    if(m_settings != nullptr){
        m_settings->setInterfaceName(device);
        emit deviceChanged();
    }
}

QString AbstractConnectionSettingsInterface::getConName()
{

    QString ret = "";

    if(m_connection !=  NULL){
        ret = m_settings->id();
    }
    return ret;
}

void AbstractConnectionSettingsInterface::setConName(QString p_conName)
{
    m_settings->setId(p_conName);
    emit conNameChanged();
}
