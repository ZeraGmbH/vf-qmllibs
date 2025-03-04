#ifndef TEST_TIMEZONE_BASE_MODEL_H
#define TEST_TIMEZONE_BASE_MODEL_H

#include <QObject>

class test_timezone_base_model : public QObject
{
    Q_OBJECT
private slots:
    void earlyConnectionStart();
    void lateConnectionStart();
    void checkTimezones();
    void checkTimezonesDisplayNoTranslationSet();
    void checkTimezonesDisplayTranslationSet();
};

#endif // TEST_TIMEZONE_BASE_MODEL_H
