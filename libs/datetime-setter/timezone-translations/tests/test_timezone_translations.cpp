#include "test_timezone_translations.h"
#include "timezonetranslations.h"
#include <QTest>

QTEST_MAIN(test_timezone_translations)

void test_timezone_translations::translateNoLanguageSet()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    QCOMPARE(tzTrans.translate("Asia/Jakarta"), "Asia/Jakarta");
}

void test_timezone_translations::translateGerman()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    tzTrans.setLanguage("de_DE");
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europa/Zürich");
}

void test_timezone_translations::translateUsOrInvalid()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    tzTrans.setLanguage("en_US");
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europe/Zurich");
}

void test_timezone_translations::switchGermanTwice()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    tzTrans.setLanguage("de_DE");
    tzTrans.setLanguage("de_DE");
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europa/Zürich");
}

void test_timezone_translations::translateGermanSwitchFrench()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    tzTrans.setLanguage("de_DE");
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europa/Zürich");
    tzTrans.setLanguage("fr_FR");
    QCOMPARE(tzTrans.translate("Europe/Malta"), "Europe/Malte");
}
