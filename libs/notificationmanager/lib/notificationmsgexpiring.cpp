#include "notificationmsgexpiring.h"
#include <timerfactoryqt.h>

NotificationMsgExpiring::NotificationMsgExpiring(QString msg, int fadeOutTimeMs) :
    NotificationMsg(msg),
    m_fadeOutTimer(TimerFactoryQt::createSingleShot(fadeOutTimeMs))
{
    connect(m_fadeOutTimer.get(), &TimerTemplateQt::sigExpired,
            this, &NotificationMsg::sigFadeOut);
    m_fadeOutTimer->start();
}
