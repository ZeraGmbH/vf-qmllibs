#ifndef TIMEZONETRANSLATIONS_H
#define TIMEZONETRANSLATIONS_H

#include <QTranslator>
#include <QString>
#include <memory>

class TimezoneTranslations : public QObject
{
    Q_OBJECT
public:
    static QString noRegionString();
    void setLanguage(const QString &language);
    QString translate(const QString &regionOrCity) const;
signals:
    void sigLanguageChanged();

private:
    static QString noRegionStringTranslated();
    bool isDefaultAndHasNoTranslationFile(const QString &language) const;
    bool isSupportedLanguage(const QString &language) const;

    QString m_currentLanguage; // seems QTranslator::language() is not available in Qt 5.14
    std::unique_ptr<QTranslator> m_translator;

};

#endif // TIMEZONETRANSLATIONS_H
