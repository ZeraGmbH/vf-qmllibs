#include "notificationmsgexpiring.h"
#include <timerfactoryqt.h>

NotificationMsgExpiring::NotificationMsgExpiring()
{
    connect(m_fadeOutTimer.get(), &TimerTemplateQt::sigExpired,
            this, &NotificationMsgExpiring::onFaded);
    m_fadeOutTimer->start();
}

NotificationMsgExpiring::NotificationMsgExpiring(QString msg, int fadeOutTimeMs) :
    NotificationMsg(msg),
    m_fadeOutTimer(TimerFactoryQt::createSingleShot(fadeOutTimeMs))
{
    connect(m_fadeOutTimer.get(), &TimerTemplateQt::sigExpired,
            this, &NotificationMsgExpiring::onFaded);
    m_fadeOutTimer->start();
}

void NotificationMsgExpiring::setTimer(int fadeOutTimeMs)
{
    m_fadeOutTimer = TimerFactoryQt::createSingleShot(fadeOutTimeMs);
}

void NotificationMsgExpiring::onFaded()
{
    emit sigFadeOut(m_id);
}
