#ifndef VECTORSETTINGS_H
#define VECTORSETTINGS_H

#include "vectorsettingslayout.h"
#include "vectorsettingsangles.h"
#include "vectorsettingslengths.h"

struct VectorSettings {
    VectorSettingsLayout m_layout;
    VectorSettingsAngles m_angles;
    VectorSettingsLengths m_lengths;
};

#endif // VECTORSETTINGS_H
