#include "test_journalansilineconvert.h"
#include "journalansilineconvert.h"
#include <testloghelpers.h>
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(test_journalansilineconvert)

void test_journalansilineconvert::emptyLinesIgnored()
{
    QString lines = TestLogHelpers::loadFile(TESTFILE_PATH "header");
    QVERIFY(!lines.isEmpty());

    JournalAnsiLineConvert conv;
    QSignalSpy spy(&conv, &JournalAnsiLineConvert::sigParsedLine);

    conv.parseLines(lines);
    QCOMPARE(spy.count(), 1);
}

void test_journalansilineconvert::extractTimestampAndProcess()
{
    JournalAnsiLineConvert conv;
    QSignalSpy spy(&conv, &JournalAnsiLineConvert::sigParsedLine);

    QString lines = TestLogHelpers::loadFile(TESTFILE_PATH "header+two-lines");
    conv.parseLines(lines);

    QCOMPARE(spy[0][1], "");
    QCOMPARE(spy[1][1], "[    0.000000] imx6qdl-variscite-som kernel:");
    QCOMPARE(spy[2][1], "[    0.000001] imx6qdl-variscite-som kernel:");
}

void test_journalansilineconvert::header()
{
    JournalAnsiLineConvert conv;
    QSignalSpy spy(&conv, &JournalAnsiLineConvert::sigParsedLine);

    QString lines = TestLogHelpers::loadFile(TESTFILE_PATH "header");
    conv.parseLines(lines);

    QCOMPARE(spy[0][0], JournalAnsiLineConvert::HEADER);
    QCOMPARE(spy[0][1], "");
    QCOMPARE(spy[0][2], "-- Logs begin at Fri 2026-09-25 09:10:27 UTC, end at Fri 2026-09-25 10:55:39 UTC. --");
}

void test_journalansilineconvert::decodeStandardLine()
{
    JournalAnsiLineConvert conv;
    QSignalSpy spy(&conv, &JournalAnsiLineConvert::sigParsedLine);

    QString lines = TestLogHelpers::loadFile(TESTFILE_PATH "header+two-lines");
    conv.parseLines(lines);

    QCOMPARE(spy[1][0], JournalAnsiLineConvert::STANDARD);
    QCOMPARE(spy[1][2], "Booting Linux on physical CPU 0x0");
}

void test_journalansilineconvert::timestampAndProcessOnly()
{
    JournalAnsiLineConvert conv;
    QSignalSpy spy(&conv, &JournalAnsiLineConvert::sigParsedLine);

    QString lines = TestLogHelpers::loadFile(TESTFILE_PATH "timestamp-and-process-only");
    conv.parseLines(lines);

    QCOMPARE(spy[0][0], JournalAnsiLineConvert::STANDARD);
    QCOMPARE(spy[0][1], "[    0.000001] imx6qdl-variscite-som kernel:");
    QCOMPARE(spy[0][2], "");
}

void test_journalansilineconvert::boldMessage()
{
    JournalAnsiLineConvert conv;
    QSignalSpy spy(&conv, &JournalAnsiLineConvert::sigParsedLine);

    QString lines = TestLogHelpers::loadFile(TESTFILE_PATH "bold-only");
    conv.parseLines(lines);

    QCOMPARE(spy[0][0], JournalAnsiLineConvert::BOLD);
    QCOMPARE(spy[0][1], "[    0.000001] imx6qdl-variscite-som kernel:");
    QCOMPARE(spy[0][2], "Linux version 6.18.53-fslc-g1ad417679718 (oe-user@oe-host) (arm-mortsgna-linux-gnueabi-gcc (GCC) 9.3.0, GNU ld (GNU Binutils) 2.34.0.20200220) #1 SMP Thu Sep 24 08:05:39 UTC 2026");
}

void test_journalansilineconvert::errorMessage()
{
    JournalAnsiLineConvert conv;
    QSignalSpy spy(&conv, &JournalAnsiLineConvert::sigParsedLine);

    QString lines = TestLogHelpers::loadFile(TESTFILE_PATH "error");
    conv.parseLines(lines);

    QCOMPARE(spy[0][0], JournalAnsiLineConvert::ERROR);
    QCOMPARE(spy[0][1], "[   15.447703] zera-mt310s2-unknown avahi-daemon[758]:");
    QCOMPARE(spy[0][2], "../../avahi-0.8/avahi-daemon/chroot.c: open() failed: No such file or directory");
}

void test_journalansilineconvert::warningMessage()
{
    JournalAnsiLineConvert conv;
    QSignalSpy spy(&conv, &JournalAnsiLineConvert::sigParsedLine);

    QString lines = TestLogHelpers::loadFile(TESTFILE_PATH "warning");
    conv.parseLines(lines);

    QCOMPARE(spy[0][0], JournalAnsiLineConvert::WARNING);
    QCOMPARE(spy[0][1], "[   15.451458] zera-mt310s2-unknown avahi-daemon[750]:");
    QCOMPARE(spy[0][2], "Failed to open /etc/resolv.conf: Invalid argument");
}

void test_journalansilineconvert::debugMessage()
{
    JournalAnsiLineConvert conv;
    QSignalSpy spy(&conv, &JournalAnsiLineConvert::sigParsedLine);

    QString lines = TestLogHelpers::loadFile(TESTFILE_PATH "debug");
    conv.parseLines(lines);

    QCOMPARE(spy[0][0], JournalAnsiLineConvert::DEBUG);
    QCOMPARE(spy[0][1], "[   19.872712] zera-mt310s2-unknown mt310s2d[805]:");
    QCOMPARE(spy[0][2], "[vein-tcp] Inherited socket descriptor from systemd, listening on port: 6307");
}

void test_journalansilineconvert::auditBlueMessage()
{
    JournalAnsiLineConvert conv;
    QSignalSpy spy(&conv, &JournalAnsiLineConvert::sigParsedLine);

    QString lines = TestLogHelpers::loadFile(TESTFILE_PATH "audit-blue");
    conv.parseLines(lines);

    QCOMPARE(spy[0][0], JournalAnsiLineConvert::AUDIT);
    QCOMPARE(spy[0][1], "[    5.884777] localhost.localdomain audit[1]:");
    QCOMPARE(spy[0][2], "SERVICE_START pid=1 uid=0 auid=4294967295");
}

void test_journalansilineconvert::linesFromFedora43Host()
{
    JournalAnsiLineConvert conv;
    QSignalSpy spy(&conv, &JournalAnsiLineConvert::sigParsedLine);

    QString lines = TestLogHelpers::loadFile(TESTFILE_PATH "buildhost");
    conv.parseLines(lines);

    QCOMPARE(spy[0][0], JournalAnsiLineConvert::STANDARD);
    QCOMPARE(spy[0][1], "[    2.462883] localhost.localdomain kernel:");
    QCOMPARE(spy[0][2], "BIOS-provided physical RAM map:");

    QCOMPARE(spy[1][0], JournalAnsiLineConvert::BOLD);
    QCOMPARE(spy[1][1], "[    2.463251] localhost.localdomain kernel:");
    QCOMPARE(spy[1][2], "random: crng init done");

    QCOMPARE(spy[2][0], JournalAnsiLineConvert::WARNING);
    QCOMPARE(spy[2][1], "[    2.463551] localhost.localdomain kernel:");
    QCOMPARE(spy[2][2], "ACPI BIOS Warning (bug): Optional FADT field Pm2ControlBlock has valid Length but zero Address: 0x0000000000000000/0x1 (20251212/tbfadt-611)");

    QCOMPARE(spy[3][0], JournalAnsiLineConvert::ERROR);
    QCOMPARE(spy[3][1], "[    2.465269] localhost.localdomain kernel:");
    QCOMPARE(spy[3][2], "virt/tdx: TDX not supported by the host platform");

    QCOMPARE(spy[4][0], JournalAnsiLineConvert::DEBUG);
    QCOMPARE(spy[4][1], "[    8.681348] localhost.localdomain rtkit-daemon[1178]:");
    QCOMPARE(spy[4][2], "Canary thread running.");

    QCOMPARE(spy[5][0], JournalAnsiLineConvert::AUDIT);
    QCOMPARE(spy[5][1], "[    5.884777] localhost.localdomain audit[1]:");
    QCOMPARE(spy[5][2], "SERVICE_START pid=1 uid=0 auid=4294967295 ses=4294967295");
}
