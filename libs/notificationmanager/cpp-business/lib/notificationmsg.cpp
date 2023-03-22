#include "notificationmsg.h"

static int currentId = 0;

NotificationMsg::NotificationMsg(QString msg) :
    m_id(currentId++),
    m_msg(msg)
{
}

QString NotificationMsg::getMsg() const
{
    return m_msg;
}

int NotificationMsg::getId() const
{
    return m_id;
}

QColor NotificationMsg::getBackGroundColor()
{
    return m_backGroundColor;
}

QColor NotificationMsg::getBorderColor()
{
    return m_borderColor;
}

QColor NotificationMsg::getTextColor()
{
    return m_textColor ;
}

int NotificationMsg::getRadius()
{
    return m_radius;
}

int NotificationMsg::verticalAlignment()
{
    return m_verticalAlignment;
}

int NotificationMsg::horizontalAlignment()
{
    return m_horizontalAlignment;
}

void NotificationMsg::setBackGroundColor(QColor backGroundColor)
{
    if(m_backGroundColor != backGroundColor){
        m_backGroundColor = backGroundColor;
        emit backGroundColorChanged();
    }
}

void NotificationMsg::setBorderColor(QColor borderColor)
{
    if(m_borderColor != borderColor){
        m_borderColor = borderColor;
        emit borderColorChanged();
    }
}

void NotificationMsg::setTextColor(QColor textColor)
{
    if(m_textColor != textColor){
        m_textColor = textColor;
        emit textColorChanged();
    }
}

void NotificationMsg::setRadius(int radius)
{
    if(m_radius != radius){
        m_radius = radius;
        emit radiusChanged();
    }
}

void NotificationMsg::setVerticalAlignment(int verticalAlignment)
{
    if(m_verticalAlignment != verticalAlignment){
        m_verticalAlignment = verticalAlignment;
        emit verticalAlignmentChanged();
    }
}

void NotificationMsg::setHorizontalAlignment(int horizontalAlignment)
{
    if(m_horizontalAlignment != horizontalAlignment){
        m_horizontalAlignment = horizontalAlignment;
        emit horizontalAlignmentChanged();
    }
}
