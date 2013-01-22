#include "gameengine.h"
#include <QApplication>
#include "sleepthread.h"

GameEngine::GameEngine(GameState *game, QWidget *parent) :
    QWidget(parent),
    _gamestate(game),
    _exit(false)
{
    //set up interval in microseconds
    float interval = (1.0f / 60.0f);
    _interval_usec = (int)(interval * 1000000.0f);

    _interval_msec = (int)(_interval_usec / 1000);



    _loopControl = new QTimer(this);
    //_loopControl->setInterval(interval_msec);
    connect( _loopControl, SIGNAL(timeout()),
             this, SLOT(slotRun()) );

    _gamestate->setParent(this);
    //Constructs the game
    _gamestate->buildAssets();
    setupUi();

    //Start up the game
    _gamestate->startGame();
    //Start timeres
    _timer.start();
    _loopControl->start(_interval_msec);
}

GameEngine::~GameEngine()
{
}

void GameEngine::slotRun()
{
    //Take care of any initializations
    //QElapsedTimer theClock;
    //theClock.start();

    //Interval (framerate)


    //while( !_exit ){
    if( !_exit ){
        //handle event loop stuff
        //qApp->processEvents();

        //qDebug() << "GameEngine::run():";
        qint64 elapsed_nsec = _timer.nsecsElapsed();
        qint64 elapsed_usec = (elapsed_nsec / 1000);
        if( elapsed_usec < _interval_usec ){
            SleepThread::usleep(_interval_usec - elapsed_usec);
        }
        _timer.restart();
        float timePassedSec = (float)elapsed_usec / 1000000.0;

        //Process input
        handleInput();

        //Update game state
        _gamestate->update(timePassedSec);

        //Render
        _gamestate->renderState();

        _loopControl->start(_interval_msec);
    }

    //Handle exiting to main menu...

}

void GameEngine::handleInput()
{
    //Here's where we modify the
    //current game state based on
    //whatever the keypress events
    //did to our booleans
    _gamestate->handleInput();
}

void GameEngine::update(float dt)
{
    //Update the current game state
    //with the amount of time that
    //has passed in fractional seconds.

    //Update local player actions

    //Update networked player actions

    //Update game objects

    //Handle collision detection

}

void GameEngine::slotExit()
{
    _exit = true;
}

void GameEngine::setupUi()
{
    this->setObjectName(QString::fromUtf8("GameEngine::main"));
    _mainLayout = new QVBoxLayout();
    _mainLayout->setObjectName(QString::fromUtf8("GameEngine::mainLayout"));
    this->setLayout(_mainLayout);

    //Create the game state and display.
//    _gamestate = new PongState(680, 480, this);
    _gamestate->setObjectName(QString::fromUtf8("GameEngine::_gamestate"));

    //Add the screen as our child widget.
    _mainLayout->addWidget(_gamestate);

}

void GameEngine::makeConnections()
{
    //Connect the gameOver signal from the
    //game state to this class's exit function.
    connect( _gamestate, SIGNAL(gaveOver()),
             this, SLOT(slotExit()) );
}
