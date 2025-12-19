#include "pseudocrcbuffer.h"

PseudoCrcBuffer::PseudoCrcBuffer(QObject *parent)
    : QIODevice{parent}
{
}

quint32 PseudoCrcBuffer::getCrc() const
{
    return m_crc32;
}

bool PseudoCrcBuffer::open(OpenMode flags)
{
    if (isOpen()) {
        qWarning("PseudoCrcBuffer::open: Buffer cannot be opened more than once");
        return false;
    }
    if ((flags & (Append | Truncate)) != 0)
        flags |= WriteOnly;

    if ((flags & ReadOnly) != 0) {
        qWarning("PseudoCrcBuffer::open: Buffer cannot be opened for read");
        return false;
    }
    if ((flags & WriteOnly) == 0) {
        qWarning("PseudoCrcBuffer::open: Buffer access not specified");
        return false;
    }

    m_size = 0;
    m_crc32 = InitialCrc;
    return QIODevice::open(flags | QIODevice::Unbuffered);
}

qint64 PseudoCrcBuffer::size() const
{
    return m_size;
}

qint64 PseudoCrcBuffer::pos() const
{
    return m_size;
}

bool PseudoCrcBuffer::seek(qint64 offset)
{
    Q_UNUSED(offset)
    return false;
}

bool PseudoCrcBuffer::atEnd() const
{
    return false;
}

bool PseudoCrcBuffer::canReadLine() const
{
    return false;
}

qint64 PseudoCrcBuffer::readData(char *data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    qWarning("PseudoCrcBuffer::readData: Cannot read");
    return 0;
}

qint64 PseudoCrcBuffer::writeData(const char *data, qint64 len)
{
    m_crc32 = Crc32IsoHdlc::calcCrc32(data, len, m_crc32);
    m_size += len;
    return len;
}
