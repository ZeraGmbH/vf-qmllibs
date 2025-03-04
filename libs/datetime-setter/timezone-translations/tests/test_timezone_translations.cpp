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
    QCOMPARE(tzTrans.setLanguage("de_DE"), true);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europa/Zürich");
}

void test_timezone_translations::translateUs()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    QCOMPARE(tzTrans.setLanguage("de_DE"), true);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europa/Zürich");

    QCOMPARE(tzTrans.setLanguage("en_US"), true);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europe/Zurich");
}

void test_timezone_translations::translateC()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    QCOMPARE(tzTrans.setLanguage("de_DE"), true);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europa/Zürich");

    QCOMPARE(tzTrans.setLanguage("C"), true);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europe/Zurich");
}

void test_timezone_translations::translateInvalid()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    QCOMPARE(tzTrans.setLanguage("de_DE"), true);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europa/Zürich");

    QCOMPARE(tzTrans.setLanguage("foo"), true); // Invalid changes to en_US -> true
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europe/Zurich");

    QCOMPARE(tzTrans.setLanguage("de_DE"), true);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europa/Zürich");

    QCOMPARE(tzTrans.setLanguage("foo"), true);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europe/Zurich");
    QCOMPARE(tzTrans.setLanguage("foo"), false);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europe/Zurich");

    QCOMPARE(tzTrans.setLanguage("en_US"), true);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europe/Zurich");
}

void test_timezone_translations::switchGermanTwice()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    QCOMPARE(tzTrans.setLanguage("de_DE"), true);
    QCOMPARE(tzTrans.setLanguage("de_DE"), false);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europa/Zürich");
}

void test_timezone_translations::switchUSTwice()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    QCOMPARE(tzTrans.setLanguage("en_US"), true);
    QCOMPARE(tzTrans.setLanguage("en_US"), false);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europe/Zurich");
}

void test_timezone_translations::switchCTwice()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    QCOMPARE(tzTrans.setLanguage("C"), true);
    QCOMPARE(tzTrans.setLanguage("C"), false);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europe/Zurich");
}

void test_timezone_translations::translateGermanSwitchFrench()
{
    TimezoneTranslations tzTrans(QString(TIMEZONE_TRANSLATE_BUILD_PATH));
    QCOMPARE(tzTrans.setLanguage("de_DE"), true);
    QCOMPARE(tzTrans.translate("Europe/Zurich"), "Europa/Zürich");
    QCOMPARE(tzTrans.setLanguage("fr_FR"), true);
    QCOMPARE(tzTrans.translate("Europe/Malta"), "Europe/Malte");
}
