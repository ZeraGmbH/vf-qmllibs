#include "vectorsettingsstatic.h"

VectorSettingsStatic::VectorType VectorSettingsStatic::getVectorType(int vectorIdx)
{
    return vectorIdx < VectorSettingsStatic::COUNT_PHASES ? TYPE_U : TYPE_I;
}
