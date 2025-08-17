#ifndef TEST_COORD_CROSS_AND_CIRCLE_H
#define TEST_COORD_CROSS_AND_CIRCLE_H

#include <QObject>

class test_coord_cross_and_circle : public QObject
{
    Q_OBJECT
private slots:
    void noGridSquare();
    void coordCrossOnlySquare();
    void coordCrossOnlyRectangleWide();
    void coordCrossOnlyRectangleNarrow();
    void coordCrossOnlyBlue();

    void coordCrossAndCircleNoOvershoot();
    void coordCrossAndCircleOvershoot();
    void coordCrossAndCircleBlue();
    void coordCrossAndCircleLineWidth();
};

#endif // TEST_COORD_CROSS_AND_CIRCLE_H
