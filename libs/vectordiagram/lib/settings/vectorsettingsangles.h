#ifndef VECTORSETTINGSANGLES_H
#define VECTORSETTINGSANGLES_H

class VectorSettingsAngles
{
public:
    void setOffsetAngle(float offsetAngle);
    float getOffsetAngle() const;
    enum RotationDirection {
        Mathehmatical,
        Clockwise
    };
    void setRotationDirection(RotationDirection direction);
    RotationDirection getRotationDirection() const;
private:
    float m_offsetAngle = 0.0;
    RotationDirection m_rotationDirection;
};

#endif // VECTORSETTINGSANGLES_H
