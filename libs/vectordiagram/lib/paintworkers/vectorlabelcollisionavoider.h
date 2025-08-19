#ifndef VECTORLABELCOLLISIONAVOIDER_H
#define VECTORLABELCOLLISIONAVOIDER_H

#include "pixvectorshown.h"
#include "vectorsettingsuser.h"

class VectorLabelCollisionAvoider
{
public:
    static PixVectorsShown getCollisionAdjVectors(const PixVectorsShown &shownVectors,
                                                  const VectorSettingsUser::VectorType &vectorType);
};

#endif // VECTORLABELCOLLISIONAVOIDER_H
