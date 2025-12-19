#ifndef TEST_PSEUDO_CRC_BUFFER_H
#define TEST_PSEUDO_CRC_BUFFER_H

#include <QObject>

class test_pseudo_crc_buffer : public QObject
{
    Q_OBJECT
private slots:
    void defaultNotOpen();
    void cannotOpenForRead();
    void canOpenForWrite();
    void canOpenForDefault();
    void cannotOpenTwice();
    void reopenResetsCount();
    void reopenResetsCrc();

    void writeCheckLen();

    void singleValue();
    void sequence();
};

#endif // TEST_PSEUDO_CRC_BUFFER_H
