#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QSizePolicy>
#include <QScreen>


#include <grille.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timerTime = 0;
    oldTimerTime = timerTime;
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDisplay);

    QScreen *screen = ui->centralwidget->screen();
    QRect  screenGeometry = screen->geometry();
    int sheight = screenGeometry.height();
    int swidth = screenGeometry.width();
    int height = ui->centralwidget->height();
    int width = ui->centralwidget->width();
    if( (swidth - width) / 2 > 320 ) {
        move(320, 60);
    }else {
        move(  (swidth - width) / 2 ,(sheight - height) / 2 );
    }
    initBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBoard() {
    g = Grille();
    for(int i = 0; i < 53; i++) {
        for(int j = 0; j < 127; j++) {
            QPushButton *cell = new QPushButton("");
            cell->setEnabled(false);
            cell->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            cell->setMaximumSize(10,10);
            if(g.getAnimalAtCoord(i, j)->getType() == Type::fox) {
                cell->setStyleSheet("background-color: red;"
                                    "border: none;");
            } else if(g.getAnimalAtCoord(i, j)->getType() == Type::rabbit) {
                cell->setStyleSheet("background-color: cyan;"
                                    "border: none;");
            }else {
                cell->setStyleSheet("background-color: rgb(40, 40, 40);"
                                    "border: none;");
            }
            ui->gridLayout->addWidget(cell, i, j, 1, 1);
        }
    }

    QPair<int,int> popCount = g.popCount();
    ui->RabPop->setText("Rabbit Population: " + QString::number(popCount.first));
    ui->FoxPop->setText("Fox Population: " + QString::number(popCount.second));
}

void MainWindow::updateGrid(Grille g) {
    for(int i = 0; i < 53; i++) {
        for(int j = 0; j < 127; j++) {
            QLayoutItem *item = ui->gridLayout->itemAtPosition(i,j);
            QWidget* widget = item->widget();
            QPushButton* cell = dynamic_cast<QPushButton*>(widget);
            if(g.getAnimalAtCoord(i, j)->getType() == Type::fox) {
                cell->setStyleSheet("background-color: red;"
                                    "border: none;");
            } else if(g.getAnimalAtCoord(i, j)->getType() == Type::rabbit) {
                cell->setStyleSheet("background-color: cyan;"
                                    "border: none;");
            }else {
                cell->setStyleSheet("background-color: rgb(40, 40, 40);"
                                    "border: none;");
            }
        }
    }
    QPair<int,int> popCount = g.popCount();
    ui->RabPop->setText(QString("Rabbit Population: " + QString::number(popCount.first)));
    ui->FoxPop->setText(QString("Fox Population: " + QString::number(popCount.second)));
}


void MainWindow::on_BtnQuit_clicked()
{
    close();
}


void MainWindow::on_BtnRestart_clicked()
{
    g = Grille();
    updateGrid(g);
}

void MainWindow::updateDisplay() {
    g.updateGrille();
    updateGrid(g);
}


void MainWindow::on_BtnPause_clicked()
{
    if(not paused) {
        paused = true;
        timerTime = 2147483647;
        timer->start(timerTime);
        return;
    }else {
        paused = false;
        timerTime = oldTimerTime;
        timer->start(timerTime);
    }

}

