#ifndef PONGSTATE_H
#define PONGSTATE_H

#include "gamestate.h"

class PongState : public GameState
{
    Q_OBJECT

public:
    PongState(int screenWidth, int screenHeight,
              QObject *parent=0);

    ~PongState();

    void buildAssets();

signals:

public slots:

private:

    GameObject* _playerOne;

    GameObject* _playerTwo;

    GameObject* _ball;

    GameObject* _topWall;

    GameObject* _bottomWall;

};

#endif // PONGSTATE_H
