#ifndef VECTORSETTINGSUSER_H
#define VECTORSETTINGSUSER_H

#include <QObject>

enum class VectorStandard : int
{
    DIN,
    IEC,
    ANSI
};

Q_DECLARE_METATYPE(VectorStandard)

enum class VectorType : int
{
    STAR = 0,
    TRIANGLE = 1,
    THREE_PHASE = 2
};

Q_DECLARE_METATYPE(VectorType)

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
