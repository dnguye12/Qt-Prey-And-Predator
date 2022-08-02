#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "grille.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    //functions
    void initBoard();

    void updateGrid(Grille g);

private slots:
    void on_BtnQuit_clicked();

    void on_BtnRestart_clicked();

    void on_BtnPause_clicked();

private:
    Ui::MainWindow *ui;
    Grille g;
};
#endif // MAINWINDOW_H
