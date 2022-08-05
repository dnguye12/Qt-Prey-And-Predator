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
    ui->BtnPause->setToolTip("Start The Simulation");
    initBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBoard() {
    g = Grille();

    QGraphicsScene *scene;
    QImage image(127, 53, QImage::Format_RGB32);
    QRgb red;
    QRgb cyan;
    QRgb black;


    red = QColor("red").rgb();
    cyan = QColor("cyan").rgb();
    black = QColor("black").rgb();
    image.fill(black);
    Population pop = g.getPop();

    for(int i = 0; i < pop.size(); i++) {
        if(pop.getByIndex(i)->getType() == Type::fox) {
            Animal* a = pop.getByIndex(i);
            image.setPixel(a->getCoord().getCol(), a->getCoord().getRow(), red);
        }

        if(pop.getByIndex(i)->getType() == Type::rabbit) {
            Animal* a = pop.getByIndex(i);
            image.setPixel(a->getCoord().getCol(), a->getCoord().getRow(), cyan);
        }
    }
    image = image.scaledToHeight(530, Qt::FastTransformation);


    scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(image));
    scene->setSceneRect(image.rect());

    ui->graphicsView->setScene(scene);

    QPair<int,int> popCount = g.popCount();
    ui->RabPop->setText("Rabbit Population: " + QString::number(popCount.first));
    ui->FoxPop->setText("Fox Population: " + QString::number(popCount.second));
}

void MainWindow::updateGrid(Grille g) {
    QGraphicsScene *scene;
    QImage image(127, 53, QImage::Format_RGB32);
    QRgb red;
    QRgb cyan;
    QRgb black;


    red = QColor("red").rgb();
    cyan = QColor("cyan").rgb();
    black = QColor("black").rgb();
    image.fill(black);
    Population pop = g.getPop();

    for(int i = 0; i < pop.size(); i++) {
        if(pop.getByIndex(i)->getType() == Type::fox) {
            Animal* a = pop.getByIndex(i);
            image.setPixel(a->getCoord().getCol(), a->getCoord().getRow(), red);
        }

        if(pop.getByIndex(i)->getType() == Type::rabbit) {
            Animal* a = pop.getByIndex(i);
            image.setPixel(a->getCoord().getCol(), a->getCoord().getRow(), cyan);
        }
    }
    image = image.scaledToHeight(530, Qt::FastTransformation);


    scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(image));
    scene->setSceneRect(image.rect());

    ui->graphicsView->setScene(scene);

    QPair<int,int> popCount = g.popCount();
    ui->RabPop->setText("Rabbit Population: " + QString::number(popCount.first));
    ui->FoxPop->setText("Fox Population: " + QString::number(popCount.second));
}


void MainWindow::on_BtnQuit_clicked()
{
    close();
}


void MainWindow::on_BtnRestart_clicked()
{
    g = Grille();
    updateGrid(g);
    paused = true;
    timerTime = 2147483647;
    timer->start(timerTime);
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

        ui->BtnPause->setIcon(QIcon(":/images/Square Buttons/Play Square Button.png"));
        ui->BtnPause->setToolTip("Resume The Simulation");
        return;
    }else {
        paused = false;
        timerTime = oldTimerTime;
        timer->start(timerTime);

        ui->BtnPause->setIcon(QIcon(":/images/Square Buttons/Pause Square Button.png"));
        ui->BtnPause->setToolTip("Pause The Simulation");
        return;
    }

}

