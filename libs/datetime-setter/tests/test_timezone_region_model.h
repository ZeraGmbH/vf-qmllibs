#ifndef TEST_TIMEZONE_REGION_MODEL_H
#define TEST_TIMEZONE_REGION_MODEL_H

#include "timezonetranslations.h"
#include "abstracttimedate1connection.h"
#include <memory>

class test_timezone_region_model : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void earlyConnectionStart();
    void lateConnectionStart();
    void checkRegions();
    void checkRegionsTranslatedNoTranslationSet();
    void checkRegionsTranslatedTranslationSetEarly();
    void checkRegionsTranslatedTranslationSetLate();

private:
    std::shared_ptr<TimezoneTranslations> m_translations;
    std::shared_ptr<AbstractTimedate1Connection> m_timeDateConnection;
};

#endif // TEST_TIMEZONE_REGION_MODEL_H
