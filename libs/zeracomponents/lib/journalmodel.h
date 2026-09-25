#ifndef JOURNALMODEL_H
#define JOURNALMODEL_H

#include "journalansilineconvert.h"
#include <QAbstractListModel>
#include <QDateTime>
#include <QProcess>
#include <QVector>

class JournalModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        TimestampRole = Qt::UserRole + 1,
        TypeRole,
        MessageRole
    };
    Q_ENUM(Roles)

    static void registerQml();
    explicit JournalModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void start(bool follow);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void clear();

private slots:
    void readJournalOutput();
    void onParsedLine(JournalAnsiLineConvert::JournalLineType lineType,
                      const QString &timeStampAndProcess,
                      const QString &message);
private:
    struct Entry {
        JournalAnsiLineConvert::JournalLineType type;
        QString timestampStr;
        QString message;
    };
    QVector<Entry> m_entries;
    QProcess m_journalctlProces;
    QByteArray m_pendingData;
    JournalAnsiLineConvert m_journalLineParser;
};

#endif // JOURNALMODEL_H
