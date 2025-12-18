#include "test_crc32_iso_hdlc.h"
#include "pseudocrcbuffer.h"
#include <QTest>

QTEST_MAIN(test_crc32_iso_hdlc)

void test_crc32_iso_hdlc::value1()
{
    quint32 crc = PseudoCrcBuffer::calcCrc32IsoHdlc(PseudoCrcBuffer::InitialCrc, "1234567890", 10);
    // https://crccalc.com/?crc=1234567890&method=CRC-32/ISO-HDLC&datatype=ascii&outtype=hex
    QCOMPARE(crc, 0x261DAEE5);
}

void test_crc32_iso_hdlc::value2()
{
    quint32 crc = PseudoCrcBuffer::calcCrc32IsoHdlc(PseudoCrcBuffer::InitialCrc, "0987654321", 10);
    // https://crccalc.com/?crc=0987654321&method=CRC-32/ISO-HDLC&datatype=ascii&outtype=hex
    QCOMPARE(crc, 0x6C2FFCE1);
}
