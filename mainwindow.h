#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineSeries>
#include "grille.h"

#include <QTimer>

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

    void initGraph(Grille g);

    void updateGraph(Grille g);

private slots:
    void on_BtnQuit_clicked();

    void on_BtnRestart_clicked();

    void on_BtnPause_clicked();

    void updateDisplay();

    void on_BtnSpeedUp_clicked();

    void on_BtnSpeedDown_clicked();

private:
    Ui::MainWindow *ui;
    Grille g;
    bool paused = true;
    bool minSpeed = false;
    bool maxSpeed = false;
    int timerTime;
    int oldTimerTime;
    QTimer *timer = new QTimer(this);

    QLineSeries *rabLine;
    QLineSeries *foxLine;
};
#endif // MAINWINDOW_H
