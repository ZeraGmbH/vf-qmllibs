#include "timezonetranslations.h"

TimezoneTranslations::TimezoneTranslations(const QString &translationFilePath) :
    m_translationFilePath(translationFilePath)
{
}

void TimezoneTranslations::setLanguage(const QString &language)
{
    if(m_translator && m_translator->language() == language)
        return;
    m_translator = std::make_unique<QTranslator>();
    const QString translationFileName = QString("timezones_%1.ts").arg(language);
    m_translator->load(translationFileName, m_translationFilePath);
}

QString TimezoneTranslations::translate(const QString &timezone)
{
    if(!m_translator)
        return timezone;
    QString tr = m_translator->translate("", timezone.toLocal8Bit());
    if(tr.isEmpty())
        return timezone;
    return tr;
}
