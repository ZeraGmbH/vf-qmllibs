#include "nmcppnotification.h"


NmCppNotification* NmCppNotification::m_exemplar = nullptr;

NmCppNotification::NmCppNotification(QObject *parent) : QObject(parent)
{
    m_exemplar=this;
}

NmCppNotification::~NmCppNotification()
{
    m_exemplar=nullptr;
}

void NmCppNotification::sendNotifiaction(QString p_head, QString p_text)
{
    if(m_exemplar != nullptr){
        emit m_exemplar->notification(p_head,p_text);
    }
}
