#include "timezonetranslations.h"
#include <zeratranslation.h>
#include <QFile>

static const char* noRegionLabel = "other";
static const char* noRegionStr = "<other>";

QString TimezoneTranslations::noRegionString()
{
    return noRegionStr;
}

void TimezoneTranslations::setLanguage(const QString &language)
{
    Q_INIT_RESOURCE(timezonetranslations);
    if (m_currentLanguage == language)
        return;

    m_translator = std::make_unique<QTranslator>();
    m_currentLanguage = language;

    if (isDefaultAndHasNoTranslationFile(language)) {
        emit sigLanguageChanged();
        return;
    }
    if (!isSupportedLanguage(language)) {
        qWarning("Timezone translation not found for language '%s'", qPrintable(language));
        emit sigLanguageChanged();
        return;
    }

    const QString translationFileName = QString("timezones_%1.qm").arg(language);
    m_translator->load(translationFileName, ":/");
    emit sigLanguageChanged();
}

QString TimezoneTranslations::translate(const QString &regionOrCity) const
{
    QString tr = regionOrCity;
    if (m_translator) {
        tr = m_translator->translate("", regionOrCity.toLocal8Bit());
        if (tr.isEmpty()) {
            if(regionOrCity == noRegionStr)
                tr = noRegionStringTranslated();
            else
                tr = regionOrCity;
        }
    }
    return tr.replace("_", " ");
}

QString TimezoneTranslations::noRegionStringTranslated()
{
    return QString("<%1>").arg(ZeraTranslation::getInstance()->trValue(noRegionLabel).toString());
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
