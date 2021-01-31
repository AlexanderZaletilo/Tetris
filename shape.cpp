#include "shape.h"

int Round(double x)
{
    return  (x >= 0) ? static_cast<int>(x + 0.5) : static_cast<int>(x - 0.5);
}
MyShape::MyShape(const QPoint &center_canvas,const QPoint &center_field , const Qt::GlobalColor &color )
{
    rects = new QRect*[4];
    this->center_canvas = center_canvas;
    this->center_field = center_field;
    this->color = color;
}
bool MyShape::isColission(bool **field)
{
    for(int i = 0; i < 4; i++)
        if(coordinates_field[i].x() < 0 || coordinates_field[i].x() > 9 ||  coordinates_field[i].y() < 0 || coordinates_field[i].y() > 19 )
            return true;
    for(int i = 0; i < 4 ; i++)
        if(field[coordinates_field[i].x()][coordinates_field[i].y()] == true)
            return true;
    return false;
}
bool MyShape::isAllowedToFall(bool **field)
{
    for(int i = 0; i < 4; i++)
        if(coordinates_field[i].y() + 1 > 19 || (field[coordinates_field[i].x()][coordinates_field[i].y() + 1] == 1 && !coordinates_field.contains(QPoint(coordinates_field[i].x(), coordinates_field[i].y() + 1))))
             return false;
    return true;
}
void MyShape::fillCanvasCoordinatesByField()
{
    for(int i = 0; i < 4; i++)
        rects[i] = new QRect(coordinates_field[i].x() * CUBE_SIDE, coordinates_field[i].y() * CUBE_SIDE, CUBE_SIDE, CUBE_SIDE);
}
void MyShape::fillFieldCoordinatesByCanvas()
{
    for(int i = 0; i < 4; i++)
        coordinates_field.push_back(QPoint(Round(static_cast<double>(rects[i]->x()) / CUBE_SIDE ), Round(static_cast<double>(rects[i]->y()) / CUBE_SIDE)));
}
L_Form::L_Form(const QPoint &center_canvas, const QPoint &center_field) : MyShape (center_canvas, center_field, Qt::darkRed)
{
    coordinates_field.push_back(QPoint(center_field.x(), center_field.y() - 1));
    coordinates_field.push_back(QPoint(center_field.x(), center_field.y()));
    coordinates_field.push_back(QPoint(center_field.x(), center_field.y() + 1));
    coordinates_field.push_back(QPoint(center_field.x() + 1, center_field.y() + 1));
    fillCanvasCoordinatesByField();
}
J_Form::J_Form(const QPoint &center_canvas, const QPoint &center_field) : MyShape (center_canvas, center_field, Qt::darkGreen)
{
    coordinates_field.push_back(QPoint(center_field.x(), center_field.y() - 1));
    coordinates_field.push_back(QPoint(center_field.x(), center_field.y()));
    coordinates_field.push_back(QPoint(center_field.x(), center_field.y() + 1));
    coordinates_field.push_back(QPoint(center_field.x() - 1, center_field.y() + 1));
    fillCanvasCoordinatesByField();
}
I_Form::I_Form(const QPoint &center_canvas, const QPoint &center_field) : MyShape (center_canvas, center_field, Qt::darkBlue)
{
    rects[0] = new QRect(center_canvas.x() - CUBE_SIDE * 2, center_canvas.y(), CUBE_SIDE, CUBE_SIDE);
    rects[1] = new QRect(center_canvas.x() - CUBE_SIDE, center_canvas.y(), CUBE_SIDE, CUBE_SIDE);
    rects[2] = new QRect(center_canvas.x(), center_canvas.y(), CUBE_SIDE, CUBE_SIDE);
    rects[3] = new QRect(center_canvas.x() + CUBE_SIDE, center_canvas.y(), CUBE_SIDE, CUBE_SIDE);
    fillFieldCoordinatesByCanvas();
}
T_Form::T_Form(const QPoint &center_canvas, const QPoint &center_field) : MyShape (center_canvas, center_field, Qt::darkYellow)
{
    coordinates_field.push_back(QPoint(center_field.x(), center_field.y() - 1));
    coordinates_field.push_back(QPoint(center_field.x() - 1, center_field.y()));
    coordinates_field.push_back(QPoint(center_field.x(), center_field.y()));
    coordinates_field.push_back(QPoint(center_field.x() + 1, center_field.y()));
    fillCanvasCoordinatesByField();
}
O_Form::O_Form(const QPoint &center_canvas, const QPoint &center_field) : MyShape (center_canvas, center_field, Qt::darkGray)
{
    rects[0] = new QRect(center_canvas.x() - CUBE_SIDE , center_canvas.y() - CUBE_SIDE, CUBE_SIDE, CUBE_SIDE);
    rects[1] = new QRect(center_canvas.x() , center_canvas.y() - CUBE_SIDE, CUBE_SIDE, CUBE_SIDE);
    rects[2] = new QRect(center_canvas.x() - CUBE_SIDE, center_canvas.y(), CUBE_SIDE, CUBE_SIDE);
    rects[3] = new QRect(center_canvas.x() , center_canvas.y(), CUBE_SIDE, CUBE_SIDE);
    fillFieldCoordinatesByCanvas();
}
Z_Left_Form::Z_Left_Form(const QPoint &center_canvas, const QPoint &center_field) : MyShape (center_canvas, center_field, Qt::darkCyan)
{
    coordinates_field.push_back(QPoint(center_field.x() - 1, center_field.y()));
    coordinates_field.push_back(QPoint(center_field.x() , center_field.y()));
    coordinates_field.push_back(QPoint(center_field.x(), center_field.y() - 1));
    coordinates_field.push_back(QPoint(center_field.x() + 1, center_field.y() - 1));
    fillCanvasCoordinatesByField();
}
Z_Right_Form::Z_Right_Form(const QPoint &center_canvas, const QPoint &center_field) : MyShape (center_canvas, center_field, Qt::darkMagenta)
{
    coordinates_field.push_back(QPoint(center_field.x() - 1, center_field.y() - 1));
    coordinates_field.push_back(QPoint(center_field.x() , center_field.y() - 1));
    coordinates_field.push_back(QPoint(center_field.x(), center_field.y() ));
    coordinates_field.push_back(QPoint(center_field.x() + 1, center_field.y()));
    fillCanvasCoordinatesByField();
}


