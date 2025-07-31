#ifndef TEST_VECTOR_DIAGRAM_GUI_H
#define TEST_VECTOR_DIAGRAM_GUI_H

#include <QObject>
#include <QSvgGenerator>
#include <memory>

class test_vector_diagram_gui : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void init();
    void gridOnlySquare();
    void gridOnlyRectangleWide();
    void gridOnlyRectangleNarrow();
private:
    std::unique_ptr<QSvgGenerator> m_generator;
};

#endif // TEST_VECTOR_DIAGRAM_GUI_H
