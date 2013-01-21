#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
QMainWindow(parent),
  _screen(NULL)
{
    setupUi();
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::setupUi()
{
    _main = new QWidget(this);
    _main->setObjectName(QString("MainWindow::_main"));

    _mainLayout = new QVBoxLayout();
    _mainLayout->setObjectName(QString("MainWindow::_mainLayout"));
    _main->setLayout(_mainLayout);

    _screen = new GameEngine(_main);
    _screen->setObjectName(QString("MainWindow::_screen"));
    _mainLayout->addWidget(_screen);

    setCentralWidget(_main);
}
