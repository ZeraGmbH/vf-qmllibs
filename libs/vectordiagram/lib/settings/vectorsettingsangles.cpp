#include "vectorsettingsangles.h"

void VectorSettingsAngles::setOffsetAngle(float offsetAngle)
{
    m_offsetAngle = offsetAngle;
}

float VectorSettingsAngles::getOffsetAngle() const
{
    return m_offsetAngle;
}

void VectorSettingsAngles::setRotationDirection(RotationDirection direction)
{
    m_rotationDirection = direction;
}

VectorSettingsAngles::RotationDirection VectorSettingsAngles::getRotationDirection() const
{
    return m_rotationDirection;
}
