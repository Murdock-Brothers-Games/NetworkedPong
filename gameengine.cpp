#include "gameengine.h"
#include <QElapsedTimer>
#include "sleepthread.h"

GameEngine::GameEngine(GameState *game, QWidget *parent) :
    QWidget(parent),
    _gamestate(game)
{
    _gamestate->setParent(this);
    setupUi();
}

GameEngine::~GameEngine()
{

}

void GameEngine::run()
{
    //Take care of any initializations
    QElapsedTimer theClock;
    theClock.start();

    //Interval (framerate)
    float interval = (1.0f / 60.0f);
    qint64 interval_usec = (int)(interval * 1000000.0f);

    while( !_exit ){
        qint64 elapsed_nsec = theClock.nsecsElapsed();
        qint64 elapsed_usec = (elapsed_nsec / 1000);
        if( elapsed_usec < interval_usec ){
            SleepThread::usleep(interval_usec - elapsed_usec);
        }
        theClock.restart();
        float timePassedSec = (float)elapsed_usec * 1000000.0;

        //Process input
        handleInput();

        //Update game state
        _gamestate->update(timePassedSec);

        //Render
        _gamestate->renderState();
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
