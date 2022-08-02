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
            if(g.getAnimalAtCoord(i, j).getType() == Type::fox) {
                cell->setStyleSheet("background-color: red;"
                                    "border: none;");
            } else if(g.getAnimalAtCoord(i, j).getType() == Type::rabbit) {
                cell->setStyleSheet("background-color: cyan;"
                                    "border: none;");
            }else {
                cell->setStyleSheet("background-color: rgb(26, 27, 29);"
                                    "border: none;");
            }
            ui->gridLayout->addWidget(cell, i, j, 1, 1);
        }
    }
}

void MainWindow::updateGrid(Grille g) {
    for(int i = 0; i < 53; i++) {
        for(int j = 0; j < 127; j++) {
            QLayoutItem *item = ui->gridLayout->itemAtPosition(i,j);
            QWidget* widget = item->widget();
            QPushButton* cell = dynamic_cast<QPushButton*>(widget);
            if(g.getAnimalAtCoord(i, j).getType() == Type::fox) {
                cell->setStyleSheet("background-color: red;"
                                    "border: none;");
            } else if(g.getAnimalAtCoord(i, j).getType() == Type::rabbit) {
                cell->setStyleSheet("background-color: cyan;"
                                    "border: none;");
            }else {
                cell->setStyleSheet("background-color: rgb(26, 27, 29);"
                                    "border: none;");
            }
        }
    }
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

