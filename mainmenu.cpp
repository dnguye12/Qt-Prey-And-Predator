#include "mainmenu.h"
#include "ui_mainmenu.h"

#include "mainwindow.h"

#include <QSizePolicy>
#include <QScreen>

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
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
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pushButton_2_clicked()
{
    close();
}


void MainMenu::on_pushButton_clicked()
{
    MainWindow *w = new MainWindow();
    w->show();
    this->hide();
    //close();
}

