#ifndef TEST_TIMEZONE_TRANSLATIONS_H
#define TEST_TIMEZONE_TRANSLATIONS_H

#include <QObject>

class test_timezone_translations : public QObject
{
    Q_OBJECT
private slots:
    void translateNoLanguageSet();
    void translateGerman();
    void translateUsOrInvalid(); // US has no translation
    void switchGermanTwice();
    void translateGermanSwitchFrench();
};

#endif // TEST_TIMEZONE_TRANSLATIONS_H
