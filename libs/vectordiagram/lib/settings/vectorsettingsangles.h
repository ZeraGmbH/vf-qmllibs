#ifndef VECTORSETTINGSANGLES_H
#define VECTORSETTINGSANGLES_H

enum class RotationDirection : int {
    Mathematical,
    Clockwise
};

class VectorSettingsAngles
{
public:
    void setOffsetAngle(float offsetAngle);
    float getOffsetAngle() const;
    void setRotationDirection(RotationDirection direction);
    RotationDirection getRotationDirection() const;
private:
    float m_offsetAngle = 0.0;
    RotationDirection m_rotationDirection = RotationDirection::Mathematical;
};

#endif // VECTORSETTINGSANGLES_H
