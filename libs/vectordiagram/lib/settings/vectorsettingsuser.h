#ifndef VECTORSETTINGSUSER_H
#define VECTORSETTINGSUSER_H

enum class VectorStandard : int
{
    DIN = 0,
    IEC = 1,
    ANSI = 2
};

enum class VectorType : int
{
    STAR = 0,
    TRIANGLE = 1,
    THREE_WIRE = 2
};

class VectorSettingsUser
{
public:
    VectorStandard getVectorStandard() const;
    void setVectorStandard(VectorStandard vectorStandard);

    VectorType getVectorType() const;
    void setVectorType(VectorType vectorType);

private:
    VectorType m_vectorType = VectorType::STAR;
    VectorStandard m_vectorStandard = VectorStandard::DIN;
};

#endif // VECTORSETTINGSUSER_H
