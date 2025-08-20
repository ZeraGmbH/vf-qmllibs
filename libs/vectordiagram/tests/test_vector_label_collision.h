#ifndef TEST_VECTOR_LABEL_COLLISION_H
#define TEST_VECTOR_LABEL_COLLISION_H

#include <QObject>

class test_vector_label_collision : public QObject
{
    Q_OBJECT
private slots:
    void detectCollisionAllSameAngle();

    void detectCollision_data();
    void detectCollision();

    void playgroundDebugInterestingCaseSingle();

    void fullMonsterForCinema_data();
    void fullMonsterForCinema();
};

#endif // TEST_VECTOR_LABEL_COLLISION_H
