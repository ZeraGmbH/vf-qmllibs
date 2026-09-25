#include "journalansilineconvert.h"

bool JournalAnsiLineConvert::m_metaRegistered = false;

JournalAnsiLineConvert::JournalAnsiLineConvert()
{
    if (!m_metaRegistered) {
        qRegisterMetaType<JournalAnsiLineConvert::JournalLineType>("JournalAnsiLineConvert::JournalLineType");
        m_metaRegistered = true;
    }
}

void JournalAnsiLineConvert::parseLines(const QString &journalLines)
{
    const QStringList lines = journalLines.split("\n", Qt::SkipEmptyParts);
    for (const QString &line : lines) {
        int timeStampPos = line.indexOf(": ");
        if (timeStampPos < 0)
            emit sigParsedLine(JournalLineType::HEADER, "", line);
        else {
            QString timeStamp = line.left(timeStampPos) + ":";
            QString ansiMsg = line.mid(timeStampPos+2);

            if (ansiMsg.startsWith("\x1B"))
                handleEscapedMsg(timeStamp, ansiMsg);
            else {
                JournalLineType type = JournalLineType::STANDARD;
                emit sigParsedLine(type, timeStamp, ansiMsg);
            }
        }
    }
}

static QString sanitizeTerminalOutput(const QString &input)
{
    QString output;

    enum State { Normal, Escape, CSI };
    State state = Normal;

    for (QChar ch : input) {
        switch (state) {
        case Normal:
            if (ch == 0x1b)
                state = Escape;
            else if (ch >= 0x20 || ch == '\n' || ch == '\t') {
                output += ch;
            }
            break;

        case Escape:
            if (ch == '[')
                state = CSI;
            else
                state = Normal;
            break;

        case CSI:
            if (ch >= 0x40 && ch <= 0x7e)
                state = Normal;
            break;
        }
    }
    return output;
}

void JournalAnsiLineConvert::handleEscapedMsg(const QString &timeStamp, const QString &ansiMsg)
{
    JournalLineType type = JournalLineType::STANDARD;
    QByteArray binMsg = ansiMsg.toLatin1();
    if (binMsg.startsWith("\x1B[0;1;39m"))
        type = JournalLineType::BOLD;
    else if (binMsg.startsWith("\x1B[0;1;31m"))
        type = JournalLineType::ERROR;
    else if (binMsg.startsWith("\x1B[0;1;38;5;185m") || binMsg.startsWith("\x1B[0;1;38:5:185m"))
        type = JournalLineType::WARNING;
    else if (binMsg.startsWith("\x1B[0;38;5;245m") || binMsg.startsWith("\x1B[0;38:5:245m"))
        type = JournalLineType::DEBUG;
    else if (binMsg.startsWith("\x1B[0;34m"))
        type = JournalLineType::AUDIT;

    emit sigParsedLine(type, timeStamp, sanitizeTerminalOutput(ansiMsg));
}
