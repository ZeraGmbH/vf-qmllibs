#include "crc32isohdlc.h"

// Based on https://lxp32.github.io/docs/a-simple-example-crc32-calculation
// tailored to subsequent stream operation
static constexpr uint32_t polynom = 0xEDB88320; // lsb implementation (0x04C11DB7 for msb-first)
static uint32_t crc32_table[256];

static void buildCrc32Table(void)
{
    static bool crcInitialized = false;
    if(!crcInitialized) {
        for (uint32_t i=0;i<256;i++) {
            uint32_t ch = i;
            uint32_t crc = 0;
            for (int bitNo=0; bitNo<8; ++bitNo) {
                uint32_t lsBit = (ch ^ crc) & 1;
                crc >>= 1;
                if (lsBit)
                    crc= crc ^ polynom;
                ch >>= 1;
            }
            crc32_table[i] = crc;
        }
        crcInitialized = true;
    }
}

uint32_t Crc32IsoHdlc::calcCrc32(const char *data, uint32_t len)
{
    return Crc32IsoHdlc::calcCrc32(data, len, InitialCrc);
}

uint32_t Crc32IsoHdlc::calcCrc32(const char *data, uint32_t len, uint32_t crc32)
{
    buildCrc32Table();
    crc32 = ~crc32;
    for (uint32_t i=0; i<len; i++) {
        char ch = data[i];
        uint8_t tabPos = (ch ^ crc32) & 0xFF;
        crc32 = (crc32 >> 8) ^ crc32_table[tabPos];
    }
    return ~crc32;
}
