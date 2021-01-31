#include "tetris.h"
#include <QMessageBox>

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
Tetris::Tetris(QWidget *parent, Ui::MainWindow *ui) : QGraphicsView(parent),
    window{ui}, sounds_on{true},  music_on{true}, game_flag{false}, currentShape{nullptr}, nextFigureIndex{0},
    currentPoints{0}, level{1}, record{0}, currentInterval{800}, lines{0}, points_modifier{1.0}
{
    rand();
    srand(time(static_cast<unsigned int>(0)));
    currentGroup = QList<QGraphicsItem*>();
    staticGroup = QList<QGraphicsItem*>();
    field = new bool*[10];
    for(int i = 0; i < 10; i++)
        field[i] = new bool[20];
    for(int i = 0; i < 10 ; i++)
        for(int j = 0; j < 20; j++)
            field[i][j] = false;
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,300,600);
    scene->setBackgroundBrush(QBrush(Qt::cyan));
    this->setScene(scene);
    nextFigureView = new QGraphicsView(parent);
    nextFigureView->setGeometry(this->x() + 390, 50, 210, 180);
    nextFigureView->show();
    nextFigureScene = new QGraphicsScene();
    nextFigureScene->setSceneRect(0,0,210,180);
    nextFigureScene->setBackgroundBrush(QBrush(Qt::cyan));
    nextFigureView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    nextFigureView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    nextFigureView->setScene(nextFigureScene);
    for(int i = 0; i < 7; i++)
        examples += QList<QGraphicsItem*>();
    this->create_nextFigure_examples();
    game_over_sound = new QSound(QDir::currentPath() + "\\game_over.wav", this);
    lines_sound = new QSound(QDir::currentPath() + "\\lines.wav", this);
    fall_sound = new QSound(QDir::currentPath() + "\\fall.wav", this);
    rotate_sound = new QSound(QDir::currentPath() + "\\move.wav", this);
    block_sound = new QSound(QDir::currentPath() + "\\block.wav", this);
    music.append(new QSound(QDir::currentPath() + "\\TetrisMix.wav", this));
    music.append(new QSound(QDir::currentPath() + "\\Tetris8Bit.wav", this));
    music.append(new QSound(QDir::currentPath() + "\\TetrisDrums.wav", this));
    music.append(new QSound(QDir::currentPath() + "\\Tetris1.wav", this));
    currentTrack = music[getRandomNumber(0, music.length() - 1)];
    linePen = QPen(Qt::black);
    timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
}
void Tetris::create_nextFigure_examples()
{
    QList<MyShape*> temp;
    temp.push_back(new L_Form(QPoint(105, 105), QPoint(3, 3)));
    temp.push_back(new J_Form(QPoint(105, 105), QPoint(3, 3)));
    temp.push_back(new T_Form(QPoint(105, 105), QPoint(3, 3)));
    temp.push_back(new I_Form(QPoint(90, 90)));
    temp.push_back(new O_Form(QPoint(90, 90)));
    temp.push_back(new Z_Left_Form(QPoint(105, 105), QPoint(3, 3)));
    temp.push_back(new Z_Right_Form(QPoint(105, 105), QPoint(3, 3)));
    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 4; j++)
        {
            examples[i] += nextFigureScene->addRect(*(temp[i]->rects[j]), linePen, QBrush(temp[i]->color));
            examples[i][j]->hide();
        }
    for(int i = 0; i < 7; i++)
        delete temp[i];
}
void Tetris::nextFigureShow()
{
    for(int i = 0; i < 4; i++)
        examples[nextFigureIndex][i]->hide();
    nextFigureIndex = static_cast<unsigned short int>(getRandomNumber(0, 6));
    for(int i = 0; i < 4; i++)
        examples[nextFigureIndex][i]->show();
}
void Tetris::drawFigure()
{
    static int x_begin = 0;
    x_begin = getRandomNumber(2, 8);
    switch(nextFigureIndex + 1)
    {
        case 1:      currentShape = new L_Form(QPoint(x_begin * MyShape::CUBE_SIDE + MyShape::HALF_CUBE_SIDE,45),QPoint(x_begin,1));            break;
        case 2:      currentShape = new J_Form(QPoint(x_begin * MyShape::CUBE_SIDE + MyShape::HALF_CUBE_SIDE,45),QPoint(x_begin,1));            break;
        case 3:      currentShape = new T_Form(QPoint(x_begin * MyShape::CUBE_SIDE + MyShape::HALF_CUBE_SIDE,45),QPoint(x_begin,1));            break;
        case 4:      currentShape = new I_Form(QPoint(x_begin * MyShape::CUBE_SIDE,30));                                                        break;
        case 5:      currentShape = new O_Form(QPoint(x_begin * MyShape::CUBE_SIDE,30));                                                        break;
        case 6:      currentShape = new Z_Left_Form(QPoint(x_begin * MyShape::CUBE_SIDE + MyShape::HALF_CUBE_SIDE,45),QPoint(x_begin,1));       break;
        case 7:      currentShape = new Z_Right_Form(QPoint(x_begin * MyShape::CUBE_SIDE + MyShape::HALF_CUBE_SIDE,45),QPoint(x_begin,1));      break;
    }
    this->nextFigureShow();
    for(int i = 0; i < 4; i++)
         currentGroup += scene->addRect(*(currentShape->rects[i]) , linePen, QBrush(currentShape->color));
    if(currentShape->isColission(field) || !currentShape->isAllowedToFall(field))
    {
        game_flag = false;
        currentTrack->stop();
        fall_sound->stop();
        if(sounds_on == true)
            game_over_sound->play();
    }
}
void Tetris::updatePoints()
{
    if(lines >= level * 5)
    {
        points_modifier += 0.1;
        level++;
        window->LevelValue->setText(QString::number(level));
        timer->setInterval(currentInterval -= static_cast<unsigned short int>(currentInterval * 0.15));
    }
    window->CurrentPointsValue->setText(QString::number(currentPoints));
}
void Tetris::updateTime()
{
    if(!currentShape->isAllowedToFall(field))
        {
            if(sounds_on == true)
                fall_sound->play();
            staticGroup += currentGroup;
            currentGroup.clear();
            int Ymax = 0;
            for(int i = 0; i < 4; i++)
            {
                field[currentShape->coordinates_field[i].x()][currentShape->coordinates_field[i].y()] = true;
                if(currentShape->coordinates_field[i].y() > Ymax)
                    Ymax = currentShape->coordinates_field[i].y();
            }
            currentPoints += static_cast<unsigned int>(points_modifier * (Ymax / 2));
            updatePoints();
            clearSolidLines(Ymax);
            this->drawFigure();
        }
    else
    {
        QKeyEvent event(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier);
        keyPressEvent(&event);
    }
    if(currentTrack->isFinished() && music_on == true)
        play_another_track();
    if(game_flag == false)
    {
        delete currentShape;
        currentShape = nullptr;
        if(currentPoints > record)
        {
            record = currentPoints;
            window->RecordValue->setText(QString::number(currentPoints));
        }
        currentTrack->stop();
        timer->stop();
        QMessageBox msgBox(this);
        QFont font;
        font.setPixelSize(22);
        msgBox.setFont(font);
        msgBox.setIcon(QMessageBox::Icon::NoIcon);
        msgBox.setWindowTitle("WASTED");
        msgBox.setText("The game is over");
        msgBox.exec();
        window->StartGame->setEnabled(true);
    }
}
void Tetris::clearSolidLines(int y)
{
    int clearedRows = 0;
    bool flag = 0;
    int count = 1;
    do
    {
        count++;
        for(int i = 0; i < 10; i++)
            if(field[i][y] == false)
            {
                flag = 1;
                y--;
                break;
            }
        if(flag == 1)
        {
            flag = 0;
            continue;
        }
        lines++;
        window->TotalLinesValue->setText(QString::number(lines));
        if(sounds_on == true)
            lines_sound->play();
        //count--;
        clearedRows++;
        QList<QGraphicsItem*> temp = scene->items(QRect(0, (y * MyShape::CUBE_SIDE) + 1, 10 * MyShape::CUBE_SIDE, MyShape::CUBE_SIDE - 10));
        for(int i = 0; i < temp.length(); i++)
        {
            staticGroup.removeOne(temp[i]);
            scene->removeItem(temp[i]);
        }

        temp = scene->items(QRect(0, 0, 10 * MyShape::CUBE_SIDE, y * MyShape::CUBE_SIDE - 1));
        for(int i = 0; i < temp.length(); i++)
            temp[i]->moveBy(0, MyShape::CUBE_SIDE);
        for(int i = 0; i < 10; i++)
            for(int j = y; j > 0; j--)
                field[i][j] = field[i][j - 1];
        for(int i = 0; i < 10; i++)
            field[i][0] = false;
    }while(count <= 4 && y >= 0);
    switch(clearedRows)
    {
        case 1:
            currentPoints += static_cast<unsigned int>(points_modifier * 100);
            break;
        case 2:
            currentPoints += static_cast<unsigned int>(points_modifier * 300);
            break;
        case 3:
            currentPoints += static_cast<unsigned int>(points_modifier * 700);
            break;
        case 4:
            currentPoints += static_cast<unsigned int>(points_modifier * 1500);
            break;
        default:
            break;
    }
    updatePoints();
}
void Tetris::rotateFigure()
{
    for(int i = 0; i < 4; i++)
        scene->removeItem(currentGroup[i]);
    currentGroup.clear();
    for(int i = 0; i < 4; i++)
         currentGroup += scene->addRect(*(currentShape->rects[i]) , linePen, QBrush(currentShape->color));
}
void Tetris::moveFigure(const QPoint &vector)
{
    foreach(QGraphicsItem *member, currentGroup)
        member->moveBy(MyShape::CUBE_SIDE * vector.x(), MyShape::CUBE_SIDE * vector.y());
}
void Tetris::startGame()
{
    currentPoints = 0;
    window->CurrentPointsValue->setText("0");
    if(music_on == true)
        play_another_track();
    scene->clear();
    currentGroup.clear();
    staticGroup.clear();
    for(int i = 0; i < 10 ; i++)
        for(int j = 0; j < 20; j++)
            field[i][j] = false;
    this->drawFigure();
    game_flag = true;
    window->LevelValue->setText("1");
    level = 1;
    lines = 0;
    points_modifier = 1.0;
    currentInterval = 1000;
    window->TotalLinesValue->setText("0");
    timer->setInterval(currentInterval);
    timer->start();
}
void Tetris::keyPressEvent(QKeyEvent *event)
{
    if(game_flag == false)
        return;
    int key = event->key();
    int vect_x = 0, vect_y = 0;
    bool rotate = false;
    switch(key)
    {
        case Qt::Key_A:
        case Qt::Key_Left:
            vect_x = -1;
            vect_y = 0;
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            vect_x = 1;
            vect_y = 0;
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            vect_x = 0;
            vect_y = 1;
            break;
        case Qt::Key_W:
        case Qt::Key_Up:
            rotate = true;
            break;
        default:    return;
    }
    if(rotate == true)
    {
        currentShape->rotate();
        if(currentShape->isColission(field))
        {
            currentShape->rotate();
            currentShape->rotate();
            currentShape->rotate();
            if(sounds_on == true)
                block_sound->play();
            return;
        }
        if(sounds_on == true)
            rotate_sound->play();
        this->rotateFigure();
    }
    else
    {
        currentShape->move(QPoint(vect_x, vect_y));
        if(currentShape->isColission(field))
        {
            currentShape->move(QPoint(-vect_x, -vect_y));
            return;
        }
        this->moveFigure(QPoint(vect_x, vect_y));
    }
}
void Tetris::turn_off_music()
{
    if(game_flag == true)
        currentTrack->stop();
    music_on = false;
}
void Tetris::turn_on_music()
{
    music_on = true;
    if(game_flag == true)
        this->play_another_track();
}
void Tetris::turn_on_sounds()
{
    sounds_on = true;
}
void Tetris::turn_off_sounds()
{
    fall_sound->stop();
    rotate_sound->stop();
    lines_sound->stop();
    block_sound->stop();
    rotate_sound->stop();
    game_over_sound->stop();
    sounds_on = false;
}
void Tetris::play_another_track()
{
    currentTrack = music[getRandomNumber(0, music.length() - 1)];
    currentTrack->play();
}
Tetris::~Tetris()
{
    delete currentTrack;
    delete block_sound;
    delete fall_sound;
    delete game_over_sound;
    delete rotate_sound;
    delete lines_sound;
    delete timer;
    delete scene;
    for(int i = 0; i < 10; i++)
        delete field[i];
    delete field;
}
