#ifndef VECTORSETTINGSUSER_H
#define VECTORSETTINGSUSER_H

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
    VectorStandard getVectorStandard() const;
    void setVectorStandard(VectorStandard vectorStandard);

    VectorType getVectorType() const;
    void setVectorType(VectorType vectorType);

private:
    VectorType m_vectorType = VectorType::VIEW_STAR;
    VectorStandard m_vectorStandard = VectorStandard::DIN;
};

#endif // VECTORSETTINGSUSER_H
