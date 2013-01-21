#ifndef PONGSTATE_H
#define PONGSTATE_H

#include "gamestate.h"

class PongState : public GameState
{
    Q_OBJECT

public:
    PongState(int screenWidth, int screenHeight,
              QWidget *parent=0);

    ~PongState();

    void buildAssets();

    //void renderState();
    void update(float dt);

    void keyPressEvent(QKeyEvent *k);

    void keyReleaseEvent(QKeyEvent *k);

signals:

public slots:

private:


    GameObject* _playerOne;

    GameObject* _playerTwo;

    GameObject* _ball;

    GameObject* _topWall;

    GameObject* _bottomWall;

    bool _p1PaddleUp, _p1PaddleDown, _p2PaddleUp, _p2PaddleDown;

};

#endif // PONGSTATE_H