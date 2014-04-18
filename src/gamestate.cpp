#include "gamestate.h"

#include <QFile>
#include <QDebug>

GameState::GameState(int screenWidth, int screenHeight,
                     QWidget *parent) :
    QWidget(parent),
    _screenWidth(screenWidth),
    _screenHeight(screenHeight)
{
    setupUi();
}

GameState::GameState(QWidget *parent):
    QWidget(parent),
    _name(QString("")),
    _screenWidth(0),
    _screenHeight(0)
{
}

GameState::~GameState()
{

}

QString GameState::getName()
{
    return _name;
}

void GameState::setName(QString name)
{
    _name = name;
}

bool GameState::hasBackdrop()
{
    return _hasBackdrop;
}

void GameState::setBackdrop(bool flag)
{
    _hasBackdrop = flag;
}

QImage GameState::getBackdropImage()
{
    return _backdrop;
}

void GameState::setBackdropImage(QImage backdrop)
{
    _backdrop = backdrop;
}

void GameState::loadBackdrop(QString filename)
{
    //Create the QImage from the filename.
    QFile theFile(filename);
    if( !theFile.exists()){
        qDebug() <<
          QString("GameState::loadBackdrop(): Error: texture file '%1' not found. (GameState '%2').").arg(
                   filename).arg(_name);
        return;
    }
    //Texture should be loaded in now.
    _backdrop.load(filename);
}

int GameState::getScreenWidth()
{
    return _screenWidth;
}

void GameState::setScreenWidth(int width)
{
    _screenWidth = width;
}

int GameState::getScreenHeight()
{
    return _screenHeight;
}

void GameState::setScreenHeight(int height)
{
    _screenHeight = height;
}

void GameState::addPlayer(GameObject* player)
{
    _players.append(player);
}

void GameState::addNonPlayer(GameObject* npc)
{
    _nonPlayers.append(npc);
}

void GameState::addScenery(GameObject* sceneItem)
{
    _scenery.append(sceneItem);
}

QList<GameObject*> GameState::getVisibleObjects()
{
    QList<GameObject*> vis;
    vis.append(_players);
    vis.append(_nonPlayers);
    vis.append(_scenery);

    return vis;
}

void GameState::renderState()
{
    //Just render the screen based on the
    //state.
    _screen->myGLRender();
}

void GameState::setupUi()
{
    this->setObjectName(QString::fromUtf8("GameState::main (StateName = %1)").arg(_name));
    _mainLayout = new QVBoxLayout();
    _mainLayout->setObjectName(QString::fromUtf8("GameState::mainLayout(StateName = %1)").arg(_name));
    this->setLayout(_mainLayout);

    //Create the display.
    _screen = new MyGLDraw(_screenWidth, _screenHeight, this);
    _screen->setObjectName(QString::fromUtf8("GameState::_screen"));

    //Add the screen as our child widget.
    _mainLayout->addWidget(_screen);
}
