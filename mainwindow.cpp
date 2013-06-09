#include "mainwindow.h"

//This is where the game declaration
//goes.
#include "pongstate.h"

MainWindow::MainWindow(QWidget *parent):
QMainWindow(parent),
  _engine(NULL)
{
    //Create our PongGame...
    _pongGame = new PongState(800, 600);

    //Setup the GUI
    setupUi();

    _soundMan = new SoundManager();

    //Run the game.
    //_engine->run();
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

    _engine = new GameEngine(_pongGame, _main);
    _engine->setObjectName(QString("MainWindow::_engine"));
    _mainLayout->addWidget(_engine);

    setCentralWidget(_main);
}
