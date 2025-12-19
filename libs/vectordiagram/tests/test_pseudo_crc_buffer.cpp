#include "test_pseudo_crc_buffer.h"
#include "pseudocrcbuffer.h"
#include <QTest>

QTEST_MAIN(test_pseudo_crc_buffer)

void test_pseudo_crc_buffer::defaultNotOpen()
{
    PseudoCrcBuffer buff;
    QCOMPARE(buff.isOpen(), false);
    QCOMPARE(buff.size(), 0);
}

void test_pseudo_crc_buffer::cannotOpenForRead()
{
    PseudoCrcBuffer buff;
    QCOMPARE(buff.open(PseudoCrcBuffer::ReadOnly), false);
    QCOMPARE(buff.isOpen(), false);
}

void test_pseudo_crc_buffer::canOpenForWrite()
{
    PseudoCrcBuffer buff;
    QCOMPARE(buff.open(PseudoCrcBuffer::WriteOnly), true);
    QCOMPARE(buff.isOpen(), true);
    QCOMPARE(buff.size(), 0);
}

void test_pseudo_crc_buffer::canOpenForDefault()
{
    PseudoCrcBuffer buff;
    QCOMPARE(buff.open(), true);
    QCOMPARE(buff.isOpen(), true);
}

void test_pseudo_crc_buffer::cannotOpenTwice()
{
    PseudoCrcBuffer buff;
    QCOMPARE(buff.open(), true);
    QCOMPARE(buff.open(), false);
    QCOMPARE(buff.isOpen(), true);
}

void test_pseudo_crc_buffer::reopenResetsCount()
{
    PseudoCrcBuffer buff;
    QCOMPARE(buff.open(), true);
    QCOMPARE(buff.writeData("12345", 5), 5);
    QCOMPARE(buff.size(), 5);
    buff.close();
    QCOMPARE(buff.open(), true);
    QCOMPARE(buff.writeData("12345", 5), 5);
    QCOMPARE(buff.size(), 5);
}

void test_pseudo_crc_buffer::reopenResetsCrc()
{
    PseudoCrcBuffer buff;
    QCOMPARE(buff.open(), true);
    QCOMPARE(buff.writeData("1234567890", 10), 10);
    buff.close();
    // https://crccalc.com/?crc=1234567890&method=CRC-32/ISO-HDLC&datatype=ascii&outtype=hex
    QCOMPARE(buff.getCrc(), 0x261DAEE5);

    QCOMPARE(buff.open(), true);
    QCOMPARE(buff.writeData("0987654321", 10), 10);
    // https://crccalc.com/?crc=0987654321&method=CRC-32/ISO-HDLC&datatype=ascii&outtype=hex
    QCOMPARE(buff.getCrc(), 0x6C2FFCE1);
}

void test_pseudo_crc_buffer::writeCheckLen()
{
    PseudoCrcBuffer buff;
    QCOMPARE(buff.open(), true);
    QCOMPARE(buff.writeData("12345", 5), 5);
    QCOMPARE(buff.size(), 5);
    QCOMPARE(buff.writeData("12345", 5), 5);
    QCOMPARE(buff.size(), 10);
}

void test_pseudo_crc_buffer::singleValue()
{
    PseudoCrcBuffer buff;
    QCOMPARE(buff.open(), true);
    QCOMPARE(buff.writeData("1234567890", 10), 10);
    // https://crccalc.com/?crc=1234567890&method=CRC-32/ISO-HDLC&datatype=ascii&outtype=hex
    QCOMPARE(buff.getCrc(), 0x261DAEE5);
}

void test_pseudo_crc_buffer::sequence()
{
    PseudoCrcBuffer buff;
    QCOMPARE(buff.open(), true);
    QCOMPARE(buff.writeData("123456", 6), 6);
    QCOMPARE(buff.writeData("7890", 4), 4);
    // https://crccalc.com/?crc=1234567890&method=CRC-32/ISO-HDLC&datatype=ascii&outtype=hex
    QCOMPARE(buff.getCrc(), 0x261DAEE5);
}
