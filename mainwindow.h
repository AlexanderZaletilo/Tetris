#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "tetris.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Tetris  *myTetris;

private slots:

    void on_StartGame_clicked();
    void on_Music_clicked();
    void on_Effects_clicked();
};
#endif // MAINWINDOW_H
