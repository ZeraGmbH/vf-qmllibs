#ifndef VECTORSETTINGSSTATIC_H
#define VECTORSETTINGSSTATIC_H

#include <QPainter>

class VectorSettingsStatic
{
public:
    static constexpr int IDX_UL1 = 0;
    static constexpr int IDX_UL2 = 1;
    static constexpr int IDX_UL3 = 2;
    static constexpr int IDX_IL1 = 3;
    static constexpr int IDX_IL2 = 4;
    static constexpr int IDX_IL3 = 5;
    static constexpr int COUNT_PHASES = 3;
    static constexpr int COUNT_VECTORS = COUNT_PHASES*2;
    enum VectorType {
        TYPE_U,
        TYPE_I
    };
    static VectorType getVectorType(int vectorIdx);
};

#endif // VECTORSETTINGSSTATIC_H
