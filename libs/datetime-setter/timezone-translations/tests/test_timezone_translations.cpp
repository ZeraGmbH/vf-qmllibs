#include "test_timezone_translations.h"
#include "timezonetranslations.h"
#include <zeratranslation.h>
#include <timemachineobject.h>
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(test_timezone_translations)

void test_timezone_translations::translateNoLanguageSet()
{
    TimezoneTranslations tzTrans;
    QCOMPARE(tzTrans.translate("Asia/Jakarta"), "Asia/Jakarta");
}

void test_timezone_translations::translateGerman()
{
    TimezoneTranslations tzTrans;
    QSignalSpy spy(&tzTrans, &TimezoneTranslations::sigLanguageChanged);
    tzTrans.setLanguage("de_DE");
    QCOMPARE(spy.count(), 1);
    QCOMPARE(tzTrans.translate("Europe"), "Europa");
    QCOMPARE(tzTrans.translate("Zurich"), "Zürich");
}

void test_timezone_translations::translateUs()
{
    TimezoneTranslations tzTrans;
    QSignalSpy spy(&tzTrans, &TimezoneTranslations::sigLanguageChanged);

    tzTrans.setLanguage("de_DE");
    QCOMPARE(spy.count(), 1);
    QCOMPARE(tzTrans.translate("Europe"), "Europa");
    QCOMPARE(tzTrans.translate("Zurich"), "Zürich");

    tzTrans.setLanguage("en_US");
    QCOMPARE(spy.count(), 2);
    QCOMPARE(tzTrans.translate("Europe"), "Europe");
    QCOMPARE(tzTrans.translate("Zurich"), "Zurich");
}

void test_timezone_translations::translateC()
{
    TimezoneTranslations tzTrans;
    QSignalSpy spy(&tzTrans, &TimezoneTranslations::sigLanguageChanged);

    tzTrans.setLanguage("de_DE");
    QCOMPARE(spy.count(), 1);
    QCOMPARE(tzTrans.translate("Europe"), "Europa");
    QCOMPARE(tzTrans.translate("Zurich"), "Zürich");

    tzTrans.setLanguage("C");
    QCOMPARE(spy.count(), 2);
    QCOMPARE(tzTrans.translate("Europe"), "Europe");
    QCOMPARE(tzTrans.translate("Zurich"), "Zurich");
}

void test_timezone_translations::translateInvalid()
{
    TimezoneTranslations tzTrans;
    QSignalSpy spy(&tzTrans, &TimezoneTranslations::sigLanguageChanged);

    tzTrans.setLanguage("de_DE");
    QCOMPARE(spy.count(), 1);
    QCOMPARE(tzTrans.translate("Europe"), "Europa");
    QCOMPARE(tzTrans.translate("Zurich"), "Zürich");

    tzTrans.setLanguage("foo"); // Invalid changes to en_US -> signal
    QCOMPARE(spy.count(), 2);
    QCOMPARE(tzTrans.translate("Europe"), "Europe");
    QCOMPARE(tzTrans.translate("Zurich"), "Zurich");

    tzTrans.setLanguage("de_DE");
    QCOMPARE(spy.count(), 3);
    QCOMPARE(tzTrans.translate("Europe"), "Europa");
    QCOMPARE(tzTrans.translate("Zurich"), "Zürich");

    tzTrans.setLanguage("foo");
    QCOMPARE(spy.count(), 4);
    QCOMPARE(tzTrans.translate("Europe"), "Europe");
    QCOMPARE(tzTrans.translate("Zurich"), "Zurich");
    tzTrans.setLanguage("foo");
    QCOMPARE(spy.count(), 4);
    QCOMPARE(tzTrans.translate("Europe"), "Europe");
    QCOMPARE(tzTrans.translate("Zurich"), "Zurich");

    tzTrans.setLanguage("en_US");
    QCOMPARE(spy.count(), 5);
    QCOMPARE(tzTrans.translate("Europe"), "Europe");
    QCOMPARE(tzTrans.translate("Zurich"), "Zurich");
}

void test_timezone_translations::switchGermanTwice()
{
    TimezoneTranslations tzTrans;
    QSignalSpy spy(&tzTrans, &TimezoneTranslations::sigLanguageChanged);

    tzTrans.setLanguage("de_DE");
    QCOMPARE(spy.count(), 1);
    tzTrans.setLanguage("de_DE");
    QCOMPARE(spy.count(), 1);
    QCOMPARE(tzTrans.translate("Europe"), "Europa");
    QCOMPARE(tzTrans.translate("Zurich"), "Zürich");
}

void test_timezone_translations::switchUSTwice()
{
    TimezoneTranslations tzTrans;
    QSignalSpy spy(&tzTrans, &TimezoneTranslations::sigLanguageChanged);

    tzTrans.setLanguage("en_US");
    QCOMPARE(spy.count(), 1);
    tzTrans.setLanguage("en_US");
    QCOMPARE(spy.count(), 1);
    QCOMPARE(tzTrans.translate("Europe"), "Europe");
    QCOMPARE(tzTrans.translate("Zurich"), "Zurich");
}

void test_timezone_translations::switchCTwice()
{
    TimezoneTranslations tzTrans;
    QSignalSpy spy(&tzTrans, &TimezoneTranslations::sigLanguageChanged);

    tzTrans.setLanguage("C");
    QCOMPARE(spy.count(), 1);
    tzTrans.setLanguage("C");
    QCOMPARE(spy.count(), 1);
    QCOMPARE(tzTrans.translate("Europe"), "Europe");
    QCOMPARE(tzTrans.translate("Zurich"), "Zurich");
}

void test_timezone_translations::translateGermanSwitchFrench()
{
    TimezoneTranslations tzTrans;
    QSignalSpy spy(&tzTrans, &TimezoneTranslations::sigLanguageChanged);

    tzTrans.setLanguage("de_DE");
    QCOMPARE(spy.count(), 1);
    QCOMPARE(tzTrans.translate("Europe"), "Europa");
    QCOMPARE(tzTrans.translate("Zurich"), "Zürich");
    tzTrans.setLanguage("fr_FR");
    QCOMPARE(spy.count(), 2);
    QCOMPARE(tzTrans.translate("Europe"), "Europe");
    QCOMPARE(tzTrans.translate("Malta"), "Malte");
}

/*void test_timezone_translations::translateGermanNoRegionUncommentOnDevEnv()
{
    TimezoneTranslations tzTrans;

    // Due to crap ZeraTranslation these are bound in TimezoneModelsFacade and here we
    // need to call both...
    tzTrans.setLanguage("de_DE");
    ZeraTranslation::getInstance()->setLanguage("de_DE");
    TimeMachineObject::feedEventLoop();

    QCOMPARE(tzTrans.translate(TimezoneTranslations::noRegionString()), "<Andere>");
}*/
