#ifndef TEST_JOURNALANSILINECONVERT_H
#define TEST_JOURNALANSILINECONVERT_H

#include <QObject>

class test_journalansilineconvert : public QObject
{
    Q_OBJECT
private slots:
    void emptyLinesIgnored();
    void extractTimestampAndProcess();
    void header();
    void decodeStandardLine();
    void timestampAndProcessOnly();
    void boldMessage();
    void errorMessage();
    void warningMessage();
    void debugMessage();
    void auditBlueMessage();

    void linesFromFedora43Host();
};

#endif // TEST_JOURNALANSILINECONVERT_H
