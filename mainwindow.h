#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "gameengine.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupUi();

    GameEngine* _screen;

    QWidget* _main;
    QVBoxLayout* _mainLayout;

};

#endif // MAINWINDOW_H
