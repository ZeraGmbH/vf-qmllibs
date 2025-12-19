#ifndef CRC32ISOHDLC_H
#define CRC32ISOHDLC_H

#include <cstdint>

class Crc32IsoHdlc
{
public:
    static constexpr uint32_t InitialCrc = ~0xFFFFFFFF;
    static uint32_t calcCrc32(const char *data, uint32_t len);
    static uint32_t calcCrc32(const char *data, uint32_t len, uint32_t crc32);
};

#endif // CRC32ISOHDLC_H
