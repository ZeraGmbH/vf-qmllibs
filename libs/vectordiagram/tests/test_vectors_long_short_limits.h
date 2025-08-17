#ifndef TEST_VECTORS_LONG_SHORT_LIMITS_H
#define TEST_VECTORS_LONG_SHORT_LIMITS_H

#include <QObject>

class test_vectors_long_short_limits : public QObject
{
    Q_OBJECT
private slots:
    void starVectorsIgnoreLessThanMin();

    void vectorLabelsTooLong_data();
    void vectorLabelsTooLong();

    void vectorLabelsTooShort_data();
    void vectorLabelsTooShort();
};

#endif // TEST_VECTORS_LONG_SHORT_LIMITS_H
