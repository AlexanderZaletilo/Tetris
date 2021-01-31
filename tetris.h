#ifndef MY_VIEW_H
#define MY_VIEW_H
#include "shape.h"
#include <QPen>
#include <QGraphicsView>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QtMultimedia/QSound>
#include <QDir>

class Tetris : public QGraphicsView
{
    Q_OBJECT
    bool **field;
    Ui::MainWindow *window;
    unsigned int record;
    unsigned int currentPoints;
    unsigned short int level;
    unsigned short int currentInterval;
    unsigned short int lines;
    double points_modifier;
    QList < QList<QGraphicsItem*> > examples;
    unsigned short int nextFigureIndex;
    QGraphicsScene *scene;
    QGraphicsView *nextFigureView;
    QGraphicsScene *nextFigureScene;
    MyShape *currentShape;
    QList<QGraphicsItem*> currentGroup;
    QList<QGraphicsItem*> staticGroup;
    QList<QSound*> music;
    QSound *currentTrack;
    QSound *block_sound;
    QSound *fall_sound;
    QSound *game_over_sound;
    QSound *rotate_sound;
    QSound *lines_sound;
    bool music_on;
    bool sounds_on;
    QPen linePen;
    QTimer *timer;
    bool game_flag;
    void create_nextFigure_examples();
    void nextFigureShow();
    void clearSolidLines(int y);
    void drawFigure();
    void moveFigure(const QPoint &vector);
    void rotateFigure();
    void updatePoints();
    void play_another_track();
public slots:
    virtual void keyPressEvent(QKeyEvent*);
public:
    explicit Tetris(QWidget *parent , Ui::MainWindow *ui);
    void startGame();
    void turn_off_music();
    void turn_off_sounds();
    void turn_on_sounds();
    void turn_on_music();
    ~Tetris();
private slots:
    void updateTime();
};
#endif // MY_VIEW_H
