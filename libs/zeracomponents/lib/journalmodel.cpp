#include "journalmodel.h"

JournalModel::JournalModel(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(&m_journalctlProces, &QProcess::readyReadStandardOutput,
            this, &JournalModel::readJournalOutput);
    connect(&m_journalLineParser, &JournalAnsiLineConvert::sigParsedLine,
            this, &JournalModel::onParsedLine);
}

int JournalModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_entries.size();
}

QVariant JournalModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
        || index.row() < 0
        || index.row() >= m_entries.size())
        return {};

    const Entry &entry = m_entries.at(index.row());

    switch (role) {
    case TimestampRole:
        return entry.timestampStr;
    case TypeRole:
        return entry.type;
    case MessageRole:
        return entry.message;
    default:
        return {};
    }
}

QHash<int, QByteArray> JournalModel::roleNames() const
{
    return {
        { TimestampRole, "timestamp" },
        { TypeRole,      "type" },
        { MessageRole,   "message" }
    };
}

void JournalModel::start(bool follow)
{
    if (m_journalctlProces.state() != QProcess::NotRunning)
        return;

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("SYSTEMD_COLORS", "1");
    m_journalctlProces.setProcessEnvironment(env);

    QStringList params = {
        QStringLiteral("-o short-monotonic"),
        QStringLiteral("--boot 0"),
        QStringLiteral("--no-pager")
    };
    if (follow)
        params.append("--follow");

    m_journalctlProces.start(QStringLiteral("journalctl"), params);
}

void JournalModel::stop()
{
    if (m_journalctlProces.state() == QProcess::NotRunning)
        return;
    m_journalctlProces.terminate();
}

void JournalModel::clear()
{
    beginResetModel();
    m_entries.clear();
    endResetModel();
}

void JournalModel::readJournalOutput()
{
    m_pendingData += m_journalctlProces.readAllStandardOutput();
    for (;;) {
        const int newline = m_pendingData.indexOf('\n');
        if (newline < 0)
            break;

        const QByteArray line = m_pendingData.left(newline);
        m_pendingData.remove(0, newline + 1);

        m_journalLineParser.parseLines(line);
    }
}

void JournalModel::onParsedLine(JournalAnsiLineConvert::JournalLineType lineType,
                                const QString &timeStampAndProcess,
                                const QString &message)
{
    const int row = m_entries.size();
    beginInsertRows(QModelIndex(), row, row);
    const Entry entry{lineType, timeStampAndProcess, message};
    m_entries.append(entry);
    endInsertRows();
}
