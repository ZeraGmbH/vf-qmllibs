#ifndef PSEUDOCRCBUFFER_H
#define PSEUDOCRCBUFFER_H

#include <QIODevice>

class PseudoCrcBuffer : public QIODevice
{
    Q_OBJECT
public:
    explicit PseudoCrcBuffer(QObject *parent = nullptr);

    quint32 getCrc() const;
    static constexpr quint32 InitialCrc = 0xFFFFFFFF;
    static quint32 calcCrc32IsoHdlc(quint32 crc32, const char *data, qint64 len) {
        // Based on https://lxp32.github.io/docs/a-simple-example-crc32-calculation/
        // Is CRC-32/ISO-HDLC - see tests
        constexpr quint32 polynom = 0xEDB88320; // lsb implementation (0x04C11DB7 for msb-first)
        for (int pos = 0; pos < len; pos++) {
            char ch = data[pos];
            for (int j=0; j<8; j++) {
                quint32 lsBit = (ch ^ crc32) & 1;
                crc32 >>= 1;
                if (lsBit)
                    crc32 = crc32 ^ polynom;
                ch>>=1;
            }
        }
        return ~crc32;
    }

    bool open(OpenMode flags) override;
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
