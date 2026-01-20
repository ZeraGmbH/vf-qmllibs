#ifndef PSEUDOCRCBUFFER_H
#define PSEUDOCRCBUFFER_H

#include "crc32isohdlc.h"
#include <QIODevice>

class PseudoCrcBuffer : public QIODevice
{
    Q_OBJECT
public:
    explicit PseudoCrcBuffer(QObject *parent = nullptr);

    quint32 getCrc() const;
    static constexpr quint32 InitialCrc = Crc32IsoHdlc::InitialCrc;

    bool open(OpenMode flags = WriteOnly) override;
    qint64 size() const override;
    qint64 pos() const override;
    bool seek(qint64 offset) override;
    bool atEnd() const override;
    bool canReadLine() const override;

    qint64 readData(char *data, qint64 maxSize) override;
    qint64 writeData(const char *data, qint64 len) override;

private:
    qint64 m_size = 0;
    quint32 m_crc32 = InitialCrc;
};

#endif // PSEUDOCRCBUFFER_H
