#include "journalmodel.h"
#include <qqml.h>

void JournalModel::registerQml()
{
    qmlRegisterType<JournalModel>("ZJournalModel", 1, 0, "ZJournalModel");
}

JournalModel::JournalModel(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(&m_journalctlProcess, &QProcess::readyReadStandardOutput,
            this, &JournalModel::readJournalOutput);
    connect(&m_journalctlProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [&](int exitCode) {
        setLoadFinished(true);
        if(exitCode != 0)
            qWarning("Process finished with error: %i", exitCode);
    });
    connect(&m_journalctlProcess, &QProcess::errorOccurred, this, [](QProcess::ProcessError error) {
        qWarning("An error occured starting journalctl: %i", error);
    });
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
    stop();
    clear();

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("SYSTEMD_COLORS", "1");
    m_journalctlProcess.setProcessEnvironment(env);

    QStringList params = {
        QStringLiteral("--no-hostname"),
        QStringLiteral("-o"), QStringLiteral("short-monotonic"),
        QStringLiteral("--boot"), QStringLiteral("0"),
        QStringLiteral("--no-pager")
    };
    if (follow)
        params.append("--follow");

    setLoadFinished(false);
    m_journalctlProcess.start(QStringLiteral("journalctl"), params);
}

bool JournalModel::getLoadFinished() const
{
    return m_processFinished;
}

void JournalModel::readJournalOutput()
{
    m_pendingData += m_journalctlProcess.readAllStandardOutput();
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

void JournalModel::stop()
{
    if (m_journalctlProcess.state() == QProcess::NotRunning)
        return;
    m_journalctlProcess.terminate();
}

void JournalModel::clear()
{
    beginResetModel();
    m_entries.clear();
    endResetModel();
}

void JournalModel::setLoadFinished(bool finished)
{
    if (finished != m_processFinished) {
        m_processFinished = finished;
        emit sigLoadFinishedChanged();
    }
}
