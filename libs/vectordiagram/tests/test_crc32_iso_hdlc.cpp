#include "test_crc32_iso_hdlc.h"
#include "crc32isohdlc.h"
#include <QTest>

QTEST_MAIN(test_crc32_iso_hdlc)

void test_crc32_iso_hdlc::value1()
{
    quint32 crc = Crc32IsoHdlc::calcCrc32("1234567890", 10);
    // https://crccalc.com/?crc=1234567890&method=CRC-32/ISO-HDLC&datatype=ascii&outtype=hex
    QCOMPARE(crc, 0x261DAEE5);
}

void test_crc32_iso_hdlc::value2()
{
    quint32 crc = Crc32IsoHdlc::calcCrc32("0987654321", 10);
    // https://crccalc.com/?crc=0987654321&method=CRC-32/ISO-HDLC&datatype=ascii&outtype=hex
    QCOMPARE(crc, 0x6C2FFCE1);
}

void test_crc32_iso_hdlc::subsequent1()
{
    quint32 crc = Crc32IsoHdlc::calcCrc32("12345", 5);
    crc = Crc32IsoHdlc::calcCrc32("67890", 5, crc);
    // https://crccalc.com/?crc=1234567890&method=CRC-32/ISO-HDLC&datatype=ascii&outtype=hex
    QCOMPARE(crc, 0x261DAEE5);
}

void test_crc32_iso_hdlc::subsequent2()
{
    quint32 crc = Crc32IsoHdlc::calcCrc32("0987", 4);
    crc = Crc32IsoHdlc::calcCrc32("654321", 6, crc);
    // https://crccalc.com/?crc=0987654321&method=CRC-32/ISO-HDLC&datatype=ascii&outtype=hex
    QCOMPARE(crc, 0x6C2FFCE1);
}
