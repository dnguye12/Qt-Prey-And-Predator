#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QSizePolicy>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBoard() {
    for(int i = 1; i <= 53; i++) {
        for(int j = 1; j <= 126; j++) {
            QPushButton *cell = new QPushButton("");
            cell->setEnabled(false);
            cell->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            cell->setMaximumSize(10,10);
            cell->setStyleSheet("background-color: rgb(26, 27, 29);"
                                "border: none;");
            ui->gridLayout->addWidget(cell, i-1, j-1, 1, 1);
        }
    }
}


void MainWindow::on_BtnQuit_clicked()
{
    close();
}

