#include "gamestate.h"

#include <QFile>
#include <QDebug>

GameState::GameState(int screenWidth, int screenHeight,
                     QWidget *parent) :
    QWidget(parent),
    _screenWidth(screenWidth),
    _screenHeight(screenHeight)
{
}

GameState::GameState(QWidget *parent):
    QWidget(parent),
    _screenWidth(0),
    _screenHeight(0),
    _name(QString(""))
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
