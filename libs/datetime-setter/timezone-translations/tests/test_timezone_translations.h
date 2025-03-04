#ifndef TEST_TIMEZONE_TRANSLATIONS_H
#define TEST_TIMEZONE_TRANSLATIONS_H

#include <QObject>

class test_timezone_translations : public QObject
{
    Q_OBJECT
private slots:
    void translateNoLanguageSet();
    void translateGerman();
    void translateUs(); // US has no translation
    void translateC(); // C has no translation
    void translateInvalid();
    void switchGermanTwice();
    void switchUSTwice();
    void switchCTwice();
    void translateGermanSwitchFrench();
};

#endif // TEST_TIMEZONE_TRANSLATIONS_H
