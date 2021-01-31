#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QTime>
#include <QTimer>
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QKeyEvent>
#include <Qt>
#include <QPainter>
#include <QRect>
#include <QPen>
#include <QGraphicsView>
#include <QGraphicsItem>
//#include "shape.h"
namespace Ui {
    class MyGraphicsView;
    class MyShape;
    class L_FORM;
    class J_FORM;
    class I_FORM;
    class O_FORM;
    class T_FORM;
    class Z_LEFT_FORM;
    class Z_RIGHT_FORM;
}
class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
    bool field[10][20];
    friend class MyShape;
    QGraphicsScene      *scene;
public:
    explicit MyGraphicsView(QWidget *parent = 0);
    MyShape *sh;
    static const int CUBE_SIDE = 30;
    MyGraphicsView();
    ~MyGraphicsView();
};

#endif // MYGRAPHICSVIEW_H
