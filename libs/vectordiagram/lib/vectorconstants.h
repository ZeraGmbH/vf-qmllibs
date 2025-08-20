#ifndef VECTORCONSTANTS_H
#define VECTORCONSTANTS_H

enum class PhaseType : int {
    TYPE_U,
    TYPE_I
};

class VectorConstants
{
public:
    static constexpr int IDX_UL1 = 0;
    static constexpr int IDX_UL2 = 1;
    static constexpr int IDX_UL3 = 2;
    static constexpr int IDX_IL1 = 3;
    static constexpr int IDX_IL2 = 4;
    static constexpr int IDX_IL3 = 5;

    static constexpr int IDX_U_START = IDX_UL1;
    static constexpr int IDX_U_END = IDX_UL3;
    static constexpr int IDX_I_START = IDX_IL1;
    static constexpr int IDX_I_END = IDX_IL3;

    static constexpr int COUNT_PHASES = 3;
    static constexpr int COUNT_VECTORS = COUNT_PHASES*2;
    static PhaseType getVectorType(int vectorIdx) {
        return vectorIdx < VectorConstants::COUNT_PHASES ? PhaseType::TYPE_U : PhaseType::TYPE_I;
    }
};

#endif // VECTORCONSTANTS_H
