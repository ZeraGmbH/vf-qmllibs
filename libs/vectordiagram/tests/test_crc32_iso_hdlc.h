#ifndef TEST_CRC32_ISO_HDLC_H
#define TEST_CRC32_ISO_HDLC_H

#include <QObject>

class test_crc32_iso_hdlc : public QObject
{
    Q_OBJECT
private slots:
    void value1();
    void value2();
    void subsequent1();
    void subsequent2();
};

#endif // TEST_CRC32_ISO_HDLC_H
