#ifndef TEST_TIMEZONE_MODEL_REGION_H
#define TEST_TIMEZONE_MODEL_REGION_H

#include "timezonetranslations.h"
#include "abstracttimedate1connection.h"
#include <memory>

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

private:
    std::shared_ptr<TimezoneTranslations> m_translations;
    std::shared_ptr<AbstractTimedate1Connection> m_timeDateConnection;
};

#endif // TEST_TIMEZONE_MODEL_REGION_H
