#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QSizePolicy>
#include <QScreen>
#include <QChart>
#include <QChartView>


#include <grille.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timerTime = 0;
    oldTimerTime = timerTime;
    minSpeed= true;
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDisplay);
    ui->BtnSpeedUp->setIcon(QIcon(":/images/Square Buttons/X Square Button.png"));

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
    //initBoard();
    initGraph(g);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBoard() {
    g = Grille();

    QGraphicsScene *scene;
    QImage image(63, 26, QImage::Format_RGB32);
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
    image = image.scaledToHeight(520, Qt::FastTransformation);


    scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(image));
    scene->setSceneRect(image.rect());

    ui->graphicsView->setScene(scene);

}

void MainWindow::updateGrid(Grille g) {
    QGraphicsScene *scene;
    QImage image(63, 26, QImage::Format_RGB32);
    QRgb red;
    QRgb cyan;
    QRgb black;


    red = QColor("red").rgb();
    cyan = QColor("cyan").rgb();
    black = QColor("black").rgb();
    image.fill(black);
    Population pop = g.getPop();

    if(pop.size() == 0) {
        on_BtnPause_clicked();
    }
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
    image = image.scaledToHeight(520, Qt::FastTransformation);


    scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(image));
    scene->setSceneRect(image.rect());

    ui->graphicsView->setScene(scene);
}

void MainWindow::initGraph(Grille g) {
    rabLine->append(0, 6);
    rabLine->append(2, 4);
    rabLine->append(3, 8);
    rabLine->append(7, 4);
    rabLine->append(10, 5);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(rabLine);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    QGraphicsScene * helper = new QGraphicsScene(this);
    //QChartView *chartView = new QChartView(chart);
    //chartView->setRenderHint(QPainter::Antialiasing);

    helper->addItem(chart);
    helper->setSceneRect(chart->rect());
    ui->popChart->setScreen(helper);
}

void MainWindow::updateGraph(Grille g) {

}

void MainWindow::updateDisplay() {
    g.updateGrille();
    updateGrid(g);
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
    ui->BtnPause->setIcon(QIcon(":/images/Square Buttons/Play Square Button.png"));
}


void MainWindow::on_BtnPause_clicked()
{
    if(not paused) {
        paused = true;
        timerTime = 2147483647;
        timer->start(timerTime);

        ui->BtnPause->setIcon(QIcon(":/images/Square Buttons/Play Square Button.png"));
        return;
    }else {
        paused = false;
        timerTime = oldTimerTime;
        timer->start(timerTime);

        ui->BtnPause->setIcon(QIcon(":/images/Square Buttons/Pause Square Button.png"));
        return;
    }

}


void MainWindow::on_BtnSpeedUp_clicked()
{
    if(not minSpeed) {
        oldTimerTime -= 250;
        if(maxSpeed) {
            maxSpeed = false;
            ui->BtnSpeedDown->setIcon(QIcon(":/images/Square Buttons/Up Square Button.png"));
        }
        if(oldTimerTime <= 0) {
            oldTimerTime = 0;
            minSpeed = true;
            ui->BtnSpeedUp->setIcon(QIcon(":/images/Square Buttons/X Square Button.png"));
        }
        timerTime = oldTimerTime;
        if(not paused) {
            timer->start(timerTime);
        }
    }
}


void MainWindow::on_BtnSpeedDown_clicked()
{
    if(not maxSpeed) {
        oldTimerTime += 250;
        if(minSpeed) {
            minSpeed = false;
            ui->BtnSpeedUp->setIcon(QIcon(":/images/Square Buttons/Down Square Button.png"));
        }
        if(oldTimerTime >= 2500) {
            oldTimerTime = 2500;
            maxSpeed = true;
            ui->BtnSpeedDown->setIcon(QIcon(":/images/Square Buttons/X Square Button.png"));
        }
        timerTime = oldTimerTime;
        if(not paused) {
            timer->start(timerTime);
        }
    }
}

