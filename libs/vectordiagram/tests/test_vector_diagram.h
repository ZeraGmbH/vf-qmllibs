#ifndef TEST_VECTOR_DIAGRAM_GUI_H
#define TEST_VECTOR_DIAGRAM_GUI_H

#include <QObject>

class test_vector_diagram : public QObject
{
    Q_OBJECT
private slots:
    void setVectorLineWidth();

    void setFontSize();

    void starVectorsNoOvershoot();
    void starVectorsNoOvershootSmall();

};

#endif // TEST_VECTOR_DIAGRAM_GUI_H
