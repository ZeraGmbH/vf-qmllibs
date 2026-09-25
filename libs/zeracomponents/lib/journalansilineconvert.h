#ifndef JOURNALANSILINECONVERT_H
#define JOURNALANSILINECONVERT_H

#include <QObject>

class JournalAnsiLineConvert : public QObject
{
    Q_OBJECT
public:
    enum JournalLineType {
        HEADER,
        STANDARD,
        BOLD,
        ERROR,
        WARNING,
        DEBUG,
        AUDIT
    };
    Q_ENUM(JournalLineType)

    JournalAnsiLineConvert();
    void parseLines(const QString &journalLines);
signals:
    void sigParsedLine(JournalAnsiLineConvert::JournalLineType lineType,
                       const QString &timeStampAndProcess,
                       const QString &message);

private:
    void handleEscapedMsg(const QString &timeStamp, const QString &ansiMsg);
    static bool m_metaRegistered;
};

#endif // JOURNALANSILINECONVERT_H
