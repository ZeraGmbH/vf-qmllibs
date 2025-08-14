#ifndef VECTORSETTINGSUSER_H
#define VECTORSETTINGSUSER_H

#include <QObject>

class VectorSettingsUser : public QObject
{
    Q_OBJECT
public:
    enum class VectorStandard : int
    {
        DIN,
        IEC,
        ANSI
    };
    Q_ENUM(VectorStandard)
    VectorStandard getVectorStandard() const;
    void setVectorStandard(VectorStandard vectorStandard);

    enum class VectorType : int
    {
        STAR,
        TRIANGLE,
        THREE_PHASE
    };
    Q_ENUM(VectorType)
    VectorType getVectorType() const;
    void setVectorType(VectorType vectorType);

private:
    VectorType m_vectorType = VectorType::STAR;
    VectorStandard m_vectorStandard = VectorStandard::DIN;
};

#endif // VECTORSETTINGSUSER_H
