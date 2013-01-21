#include "gameengine.h"

GameEngine::GameEngine(QWidget *parent) :
    QWidget(parent)
{
    setupUi();
}

GameEngine::~GameEngine()
{

}

void GameEngine::run()
{
    //Take care of any initializations

    while( !_exit ){
        //Probably need to do some
        //time keeping here, use
        //QTimer or something to keep
        //a consistent framerate.
        float timePassed = 0.0f;

        //Process input
        handleInput();

        //Update game state
        update(timePassed);

        //Render
        _screen->render();
    }

    //Handle exiting to main menu...

}

void GameEngine::handleInput()
{
    //Here's where we modify the
    //current game state based on
    //whatever the keypress events
    //did to our booleans
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

    //Create the rendering screen.
    _screen = new MyGLDraw(this);
    _screen->setObjectName(QString::fromUtf8("GameEngine::_screen"));

    //Add the screen as our child widget.
    _mainLayout->addWidget(_screen);
}
