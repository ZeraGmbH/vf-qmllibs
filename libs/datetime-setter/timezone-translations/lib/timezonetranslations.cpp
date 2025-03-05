#include "timezonetranslations.h"
#include <QFile>

bool TimezoneTranslations::setLanguage(const QString &language)
{
    Q_INIT_RESOURCE(timezonetranslations);
    if (m_currentLanguage == language)
        return false;

    m_translator = std::make_unique<QTranslator>();
    m_currentLanguage = language;

    if (isDefaultAndHasNoTranslationFile(language))
        return true;
    if (!isSupportedLanguage(language)) {
        qWarning("Timezone translation not found for language '%s'", qPrintable(language));
        return true;
    }

    const QString translationFileName = QString("timezones_%1.qm").arg(language);
    m_translator->load(translationFileName, ":/");
    return true;
}

QString TimezoneTranslations::translate(const QString &timezone) const
{
    if (!m_translator)
        return timezone;
    QString tr = m_translator->translate("", timezone.toLocal8Bit());
    if (tr.isEmpty())
        return timezone;
    return tr;
}

bool TimezoneTranslations::isDefaultAndHasNoTranslationFile(const QString &language) const
{
    return language == "C" || language == "en_US";
}

bool TimezoneTranslations::isSupportedLanguage(const QString &language) const
{
    const QString translationFileName = QString(":/timezones_%1.qm").arg(language);
    QFile file(translationFileName);
    return file.exists();
}
