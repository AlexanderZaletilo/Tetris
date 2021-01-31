#ifndef SHAPE_H
#define SHAPE_H
#include <QPoint>
#include <QList>
#include <QRect>
#include "ui_mainwindow.h"

int Round(double x);
class MyShape
{
protected:
    static const int CUBE_SIDE = 30;
    static const int HALF_CUBE_SIDE = 15;
    QPoint center_canvas;
    QPoint center_field;
    QList<QPoint> coordinates_field;
    QRect **rects;
    Qt::GlobalColor color;
public:
    MyShape(const QPoint &center_canvas = {0,0},const QPoint &center_field = {0,0}, const Qt::GlobalColor &color = Qt::red);
    virtual ~MyShape()
    {
        for(int i = 0; i < 4; i++)
            delete rects[i];
        delete rects;
    }
    bool isColission(bool **field);
    bool isAllowedToFall(bool **field);
    void fillCanvasCoordinatesByField();
    void fillFieldCoordinatesByCanvas();
    virtual void move(const QPoint &vector)
    {
        for(int i = 0; i < 4; i++)
        {
            coordinates_field[i].setX(coordinates_field[i].x() + vector.x());
            coordinates_field[i].setY(coordinates_field[i].y() + vector.y());
            rects[i]->moveTo(rects[i]->x() + vector.x() * CUBE_SIDE, rects[i]->y() + vector.y() * CUBE_SIDE);
        }
        center_field.setX(center_field.x() + vector.x());
        center_field.setY(center_field.y() + vector.y());
        center_canvas.setX(center_field.x() * CUBE_SIDE);
        center_canvas.setY(center_field.y() * CUBE_SIDE);
    }
    virtual void rotate()
    {
        int xPrev;
        for(int i = 0; i < 4; i++)
        {
            xPrev = coordinates_field[i].x();
            coordinates_field[i].setX(center_field.x() - ( coordinates_field[i].y() - center_field.y()));
            coordinates_field[i].setY(center_field.y() + ( xPrev - center_field.x()));                                                   
            rects[i]->moveTo((coordinates_field[i].x()  )* MyShape::CUBE_SIDE,coordinates_field[i].y() * MyShape::CUBE_SIDE);
        }
    }
    friend class Tetris;
};
class L_Form  : public MyShape
{
public:
    L_Form(const QPoint &center_canvas = {0,0}, const QPoint &center_field = {0,0});
    virtual ~L_Form(){}
};
class J_Form  : public MyShape
{
public:
    J_Form(const QPoint &center_canvas = {0,0}, const QPoint &center_field = {0,0});
    virtual ~J_Form(){}
};
class I_Form  : public MyShape
{
public:
    I_Form(const QPoint &center_canvas = {0,0}, const QPoint &center_field = {0,0});
    virtual void rotate() override
    {
        for(int i = 0; i < 4; i++)
        {
            rects[i]->moveTo((center_canvas.x() - rects[i]->y() + center_canvas.y() - CUBE_SIDE ),center_canvas.y() + rects[i]->x() - center_canvas.x());
            coordinates_field[i].setX(Round(static_cast<double>(rects[i]->x()) / CUBE_SIDE));
            coordinates_field[i].setY(Round(static_cast<double>(rects[i]->y()) / CUBE_SIDE));
        }
    }
    virtual void move(const QPoint &vector) override
    {
        for(int i = 0; i < 4; i++)
        {
            coordinates_field[i].setX(coordinates_field[i].x() + vector.x());
            coordinates_field[i].setY(coordinates_field[i].y() + vector.y());
            rects[i]->moveTo(rects[i]->x() + vector.x() * CUBE_SIDE, rects[i]->y() + vector.y() * CUBE_SIDE);
        }
        center_field.setX(center_field.x() + vector.x());
        center_field.setY(center_field.y() + vector.y());
        center_canvas.setX(center_canvas.x() + vector.x() * CUBE_SIDE);
        center_canvas.setY(center_canvas.y() + vector.y() * CUBE_SIDE);
    }
    virtual ~I_Form() override {}
};
class O_Form  : public MyShape
{
public:
    O_Form(const QPoint &center_canvas = {0,0}, const QPoint &center_field = {0,0});
    virtual void rotate() override
    {   }
    virtual void move(const QPoint &vector) override
    {
        for(int i = 0; i < 4; i++)
        {
            coordinates_field[i].setX(coordinates_field[i].x() + vector.x());
            coordinates_field[i].setY(coordinates_field[i].y() + vector.y());
            rects[i]->moveTo(rects[i]->x() + vector.x() * CUBE_SIDE, rects[i]->y() + vector.y() * CUBE_SIDE);
        }
        center_field.setX(center_field.x() + vector.x());
        center_field.setY(center_field.y() + vector.y());
        center_canvas.setX(center_canvas.x() + vector.x() * CUBE_SIDE);
        center_canvas.setY(center_canvas.y() + vector.y() * CUBE_SIDE);
    }
    virtual ~O_Form() override {}
};
class T_Form  : public MyShape
{
public:
    T_Form(const QPoint &center_canvas = {0,0}, const QPoint &center_field = {0,0});
    virtual ~T_Form(){}
};
class Z_Left_Form  : public MyShape
{
public:
    Z_Left_Form(const QPoint &center_canvas = {0,0}, const QPoint &center_field = {0,0});
    virtual ~Z_Left_Form(){}
};
class Z_Right_Form  : public MyShape
{
public:
    Z_Right_Form(const QPoint &center_canvas = {0,0}, const QPoint &center_field = {0,0});
    virtual ~Z_Right_Form(){}
};
#endif // SHAPE_H
