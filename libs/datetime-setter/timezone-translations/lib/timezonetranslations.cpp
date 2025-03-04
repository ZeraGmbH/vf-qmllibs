#include "timezonetranslations.h"

TimezoneTranslations::TimezoneTranslations(const QString &translationFilePath)
{
    if(translationFilePath.isEmpty())
        m_translationFilePath = QString(TIMEZONE_TRANSLATE_INSTALL_PATH);
    else
        m_translationFilePath = translationFilePath;
}

void TimezoneTranslations::setLanguage(const QString &language)
{
    if(m_currentLanguage == language)
        return;
    m_currentLanguage = language;
    m_translator = std::make_unique<QTranslator>();
    const QString translationFileName = QString("timezones_%1.ts").arg(language);
    m_translator->load(translationFileName, m_translationFilePath);
}

QString TimezoneTranslations::translate(const QString &timezone) const
{
    if(!m_translator)
        return timezone;
    QString tr = m_translator->translate("", timezone.toLocal8Bit());
    if(tr.isEmpty())
        return timezone;
    return tr;
}
