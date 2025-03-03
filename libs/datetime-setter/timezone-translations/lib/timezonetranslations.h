#ifndef TIMEZONETRANSLATIONS_H
#define TIMEZONETRANSLATIONS_H

#include <QTranslator>
#include <QString>
#include <memory>

class TimezoneTranslations
{
public:
    explicit TimezoneTranslations(const QString &translationFilePath = QString(TIMEZONE_TRANSLATE_INSTALL_PATH));
    void setLanguage(const QString &language);
    QString translate(const QString &timezone);
private:
    const QString m_translationFilePath;
    QString m_currentLanguage; // seems QTranslator::language() is not available in Qt 5.14
    std::unique_ptr<QTranslator> m_translator;

};

#endif // TIMEZONETRANSLATIONS_H
