#ifndef TEST_TIMEZONE_MODEL_REGION_H
#define TEST_TIMEZONE_MODEL_REGION_H

#include "timezonetranslations.h"
#include "abstracttimedate1connection.h"

class test_timezone_model_region : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void connectionStartEarly();
    void connectionStartLate();
    void checkRegions();
    void checkRegionsTranslatedNoTranslationSet();
    void checkRegionsTranslatedTranslationSetEarly();
    void checkRegionsTranslatedTranslationSetLate();

    void initialIndexEarly();
    void initialIndexLate();

    void setIndex0();
    void setIndexLast();
    void setIndexOutOfLimitMinusOne();
    void setIndexOutOfLimitLarge();
    void setIndexSameNoChange();
    void setIndexTwice();
    void indexChangeOnLanguageChange();
    void noIndexChangeOnLanguageChange();

private:
    TimezoneTranslationsPtr m_translations;
    AbstractTimedate1ConnectionPtr m_timeDateConnection;
};

#endif // TEST_TIMEZONE_MODEL_REGION_H
