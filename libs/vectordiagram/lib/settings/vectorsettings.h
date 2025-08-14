#ifndef VECTORSETTINGS_H
#define VECTORSETTINGS_H

#include "vectorsettingsuser.h"
#include "vectorsettingslengths.h"
#include "vectorsettingslayout.h"
#include "vectorsettingsangles.h"

struct VectorSettings {
    VectorSettingsUser m_user;
    VectorSettingsLengths m_lengths;
    VectorSettingsLayout m_layout;
    VectorSettingsAngles m_angles;
};

#endif // VECTORSETTINGS_H
