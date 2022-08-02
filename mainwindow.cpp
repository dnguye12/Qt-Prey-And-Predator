#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QSizePolicy>

#include <grille.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //initBoard();
    Grille g = Grille();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBoard() {
    for(int i = 0; i < 53; i++) {
        for(int j = 0; j < 127; j++) {
            QPushButton *cell = new QPushButton("");
            cell->setEnabled(false);
            cell->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            cell->setMaximumSize(10,10);
            cell->setStyleSheet("background-color: rgb(26, 27, 29);"
                                "border: none;");
            ui->gridLayout->addWidget(cell, i, j, 1, 1);
        }
    }
}


void MainWindow::on_BtnQuit_clicked()
{
    close();
}

