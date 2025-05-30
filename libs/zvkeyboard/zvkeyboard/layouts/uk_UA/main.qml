/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.VirtualKeyboard 2.3
import "../../" as ZVKEYB

KeyboardLayoutLoader {
    sharedLayouts: ['symbols']
    sourceComponent: InputContext.inputEngine.inputMode === InputEngine.InputMode.Cyrillic ? cyrillicLayout : latinLayout
    Component {
        id: cyrillicLayout
        KeyboardLayout {
            keyWeight: 160
            KeyboardRow {
                Key {
                    text: "й"
                }
                Key {
                    text: "ц"
                }
                Key {
                    text: "у"
                }
                Key {
                    text: "к"
                }
                Key {
                    text: "е"
                }
                Key {
                    text: "н"
                }
                Key {
                    text: "г"
                }
                Key {
                    text: "ш"
                }
                Key {
                    text: "щ"
                }
                Key {
                    text: "з"
                }
                Key {
                    text: "х"
                }
                Key {
                    text: "ї"
                }
                BackspaceKey {
                    weight: 180
                }
            }
            KeyboardRow {
                FillerKey {
                    weight: 40
                }
                Key {
                    text: "ф"
                }
                Key {
                    text: "і"
                }
                Key {
                    text: "в"
                }
                Key {
                    text: "а"
                }
                Key {
                    text: "п"
                }
                Key {
                    text: "р"
                }
                Key {
                    text: "о"
                }
                Key {
                    text: "л"
                }
                Key {
                    text: "д"
                }
                Key {
                    text: "ж"
                }
                Key {
                    text: "є"
                }
                EnterKey {
                    weight: 280
                }
            }
            KeyboardRow {
                InputModeKey {
                    inputModes: [InputEngine.InputMode.Cyrillic, InputEngine.InputMode.Latin]
                }
                Key {
                    text: "ґ"
                }
                Key {
                    text: "я"
                    alternativeKeys: "$¢я₴€¥£"
                    smallTextVisible: true
                }
                Key {
                    text: "ч"
                }
                Key {
                    text: "с"
                }
                Key {
                    text: "м"
                }
                Key {
                    text: "и"
                }
                Key {
                    text: "т"
                }
                Key {
                    text: "ь"
                }
                Key {
                    text: "б"
                }
                Key {
                    text: "ю"
                }
                Key {
                    key: Qt.Key_Period
                    text: "."
                }
                ShiftKey {
                    weight: 272
                }
            }
            KeyboardRow {
                keyWeight: 180
                ZVKEYB.DarkKey {
                    key: Qt.Key_Escape
                    displayText: "Esc"
                    showPreview: false
                }
                SymbolModeKey {
                }
                SpaceKey {
                    weight: 1000
                }
                ZVKEYB.DarkKey {
                    displayText: "\u2190"
                    key: Qt.Key_Left
                    showPreview: false
                    repeat: true
                }
                ZVKEYB.DarkKey {
                    text: "\u2192"
                    key: Qt.Key_Right
                    showPreview: false
                    repeat: true
                }
                ZVKEYB.DarkKey {
                    showPreview: false
                    key: Qt.Key_End
                    text: "End"
                }
            }
        }
    }
    Component {
        id: latinLayout
        KeyboardLayout {
            keyWeight: 160
            KeyboardRow {
                Key {
                    key: Qt.Key_Q
                    text: "q"
                }
                Key {
                    key: Qt.Key_W
                    text: "w"
                }
                Key {
                    key: Qt.Key_E
                    text: "e"
                }
                Key {
                    key: Qt.Key_R
                    text: "r"
                }
                Key {
                    key: Qt.Key_T
                    text: "t"
                }
                Key {
                    key: Qt.Key_Y
                    text: "y"
                }
                Key {
                    key: Qt.Key_U
                    text: "u"
                }
                Key {
                    key: Qt.Key_I
                    text: "i"
                }
                Key {
                    key: Qt.Key_O
                    text: "o"
                    alternativeKeys: "oö"
                }
                Key {
                    key: Qt.Key_P
                    text: "p"
                }
                BackspaceKey {}
            }
            KeyboardRow {
                FillerKey {
                    weight: 56
                }
                Key {
                    key: Qt.Key_A
                    text: "a"
                    alternativeKeys: "aåä"
                }
                Key {
                    key: Qt.Key_S
                    text: "s"
                    alternativeKeys: "sš"
                }
                Key {
                    key: Qt.Key_D
                    text: "d"
                    alternativeKeys: "dđ"
                }
                Key {
                    key: Qt.Key_F
                    text: "f"
                }
                Key {
                    key: Qt.Key_G
                    text: "g"
                }
                Key {
                    key: Qt.Key_H
                    text: "h"
                }
                Key {
                    key: Qt.Key_J
                    text: "j"
                }
                Key {
                    key: Qt.Key_K
                    text: "k"
                }
                Key {
                    key: Qt.Key_L
                    text: "l"
                }
                EnterKey {
                    weight: 283
                }
            }
            KeyboardRow {
                keyWeight: 156
                InputModeKey {
                    inputModes: [InputEngine.InputMode.Cyrillic, InputEngine.InputMode.Latin]
                }
                Key {
                    key: Qt.Key_Z
                    text: "z"
                    alternativeKeys: "zž"
                }
                Key {
                    key: Qt.Key_X
                    text: "x"
                    alternativeKeys: "$¢x₴€¥£"
                    smallTextVisible: true
                }
                Key {
                    key: Qt.Key_C
                    text: "c"
                    alternativeKeys: "ćcč"
                }
                Key {
                    key: Qt.Key_V
                    text: "v"
                }
                Key {
                    key: Qt.Key_B
                    text: "b"
                }
                Key {
                    key: Qt.Key_N
                    text: "n"
                }
                Key {
                    key: Qt.Key_M
                    text: "m"
                }
                Key {
                    key: Qt.Key_Comma
                    text: ","
                }
                Key {
                    key: Qt.Key_Period
                    text: "."
                }
                ShiftKey {
                    weight: 204
                }
            }
            KeyboardRow {
                keyWeight: 180
                ZVKEYB.DarkKey {
                    key: Qt.Key_Escape
                    displayText: "Esc"
                    showPreview: false
                }
                SymbolModeKey {
                }
                SpaceKey {
                    weight: 1000
                }
                ZVKEYB.DarkKey {
                    displayText: "\u2190"
                    key: Qt.Key_Left
                    showPreview: false
                    repeat: true
                }
                ZVKEYB.DarkKey {
                    text: "\u2192"
                    key: Qt.Key_Right
                    showPreview: false
                    repeat: true
                }
                ZVKEYB.DarkKey {
                    showPreview: false
                    key: Qt.Key_End
                    text: "End"
                }
            }
        }
    }
}
