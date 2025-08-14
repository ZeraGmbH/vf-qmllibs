#ifndef VECTORSETTINGSUSER_H
#define VECTORSETTINGSUSER_H

// enums must be in sync to PhasorDiagram::VectorType - suggestions?
enum class VectorStandard : int
{
    DIN,
    IEC,
    ANSI
};

enum class VectorType : int
{
    VIEW_STAR = 0,
    VIEW_TRIANGLE = 1,
    VIEW_THREE_PHASE = 2
};

class VectorSettingsUser
{
public:
    void setVectorStandard(VectorStandard vectorStandard);
    VectorStandard getVectorStandard() const;

    void setVectorType(VectorType vectorType);
    VectorType getVectorType() const;

private:
    VectorType m_vectorType = VectorType::VIEW_STAR;
    VectorStandard m_vectorStandard = VectorStandard::DIN;
};

#endif // VECTORSETTINGSUSER_H
