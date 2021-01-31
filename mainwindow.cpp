#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myTetris   = new Tetris(this, ui);
    myTetris->setGeometry(50,50,300,600);
    myTetris->show();
    ui->Effects->setChecked(true);
    ui->Music->setChecked(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::gray);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    ui->CurrentPointsValue->setReadOnly(true);
    ui->RecordValue->setReadOnly(true);;
    ui->TotalLinesValue->setReadOnly(true);
    ui->LevelValue->setReadOnly(true);
    ui->RecordValue->setText(QString::number(0));
    ui->CurrentPointsValue->setText(QString::number(0));
}
MainWindow::~MainWindow()
{
    delete myTetris;
    delete ui;
}
void MainWindow::on_StartGame_clicked()
{
    ui->StartGame->setEnabled(false);
    myTetris->startGame();
    myTetris->setFocus();
}
void MainWindow::on_Music_clicked()
{
    if(ui->Music->isChecked() == true)
        myTetris->turn_on_music();
    else
        myTetris->turn_off_music();
    myTetris->setFocus();
}
void MainWindow::on_Effects_clicked()
{
    if(ui->Effects->isChecked() == true)
        myTetris->turn_on_sounds();
    else
        myTetris->turn_off_sounds();
    myTetris->setFocus();
}
