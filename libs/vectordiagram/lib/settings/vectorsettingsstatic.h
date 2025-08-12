#ifndef VECTORSETTINGSSTATIC_H
#define VECTORSETTINGSSTATIC_H

#include <QPainter>

class VectorSettingsStatic
{
public:
    static constexpr int COUNT_PHASES = 3;
    static constexpr int COUNT_VECTORS = COUNT_PHASES*2;
    enum VectorType {
        TYPE_U,
        TYPE_I
    };
    static VectorType getVectorType(int vectorIdx);
};

#endif // VECTORSETTINGSSTATIC_H
