#include "mainwindow.h"

//This is where the game declaration
//goes.
#include "pongstate.h"

MainWindow::MainWindow(QWidget *parent):
QMainWindow(parent),
  _engine(NULL)
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

    //Create our PongGame...
    PongState* pongGame = new PongState(640, 480);

    _engine = new GameEngine(pongGame, _main);
    _engine->setObjectName(QString("MainWindow::_engine"));
    _mainLayout->addWidget(_engine);

    setCentralWidget(_main);
}
