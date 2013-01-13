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
    _main->setObjectName(QString("MainWindow::_centralWidget"));

    _mainLayout = new QVBoxLayout();
    _mainLayout->setObjectName(QString("MainWindow::_mainLayout"));
    _main->setLayout(_mainLayout);

    _screen = new MyGLDraw(_main);
    _screen->setObjectName(QString("MainWindow::_screenWidget"));
    _mainLayout->addWidget(_screen);

    setCentralWidget(_main);
}
