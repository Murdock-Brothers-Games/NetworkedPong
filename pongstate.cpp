#include "pongstate.h"

PongState::PongState(int screenWidth, int screenHeight,
                     QWidget* parent):
    GameState(screenWidth, screenHeight, parent),
    _p1PaddleUp(false),
    _p1PaddleDown(false),
    _p2PaddleUp(false),
    _p2PaddleDown(false)
{
    setName(QString("Pong"));
    setupUI();
    this->setFocusPolicy(Qt::StrongFocus);
}

PongState::~PongState()
{

}

void setupUI()
{

}

void render()
{

}

void PongState::buildAssets()
{
    //Build the assets for the game.
    float paddleWidth = (float)(_screenWidth) / 10.0f;
    float paddleHeight = (float)(_screenHeight) / 4.0f;
    Volume paddleVol(paddleWidth, paddleHeight, 0.0f, false);
    float paddleStartY = ((float)(_screenHeight) * 0.5f) - (paddleHeight*0.5f);

    Appearance pongAppearance;
    pongAppearance.r = 1.0f;
    pongAppearance.g = 1.0f;
    pongAppearance.b = 1.0f;
    pongAppearance.alpha = 1.0f;
    pongAppearance.textured = false;

    //Player one starting position:
    Position p1Pos(0.0f, paddleStartY, 0.0f);
    BoundingBox2D p1HBox(p1Pos, paddleVol);

    _playerOne = new GameObject("playerOne", p1Pos, this);
    _playerOne->setVolume(paddleVol);
    _playerOne->setHitBox(p1HBox);
    _playerOne->setAppearance(pongAppearance);
    _playerOne->setCollidable(true);
    _playerOne->setSolid(true);
    _playerOne->setMobile(true);
    _playerOne->setPlayable(true);
    _playerOne->setInteractive(false);

    //Player two starting position:
    Position p2Pos(_screenWidth-paddleWidth, paddleStartY, 0.0f);
    BoundingBox2D p2HBox(p2Pos, paddleVol);

    _playerTwo = new GameObject("playerTwo", p2Pos, this);
    _playerTwo->setVolume(paddleVol);
    _playerTwo->setHitBox(p2HBox);
    _playerTwo->setAppearance(pongAppearance);
    _playerTwo->setCollidable(true);
    _playerTwo->setSolid(true);
    _playerTwo->setMobile(true);
    _playerTwo->setPlayable(true);
    _playerTwo->setInteractive(false);

    //Ball
    Position ballPos((_screenWidth*0.5f),(_screenHeight*0.5f),0.0f);
    Volume ballVol(_screenWidth*0.1f, _screenHeight*0.1f, 0.0f);
    BoundingBox2D ballHBox(ballPos, ballVol);
    _ball = new GameObject("ball", ballPos, this);
    _ball->setVolume(ballVol);
    _ball->setHitBox(ballHBox);
    _ball->setAppearance(pongAppearance);
    _ball->setCollidable(true);
    _ball->setSolid(true);
    _ball->setMobile(true);
    _ball->setPlayable(false);
    _ball->setInteractive(false);

    //Walls
    Volume wallVol(_screenWidth, _screenHeight*0.1f, 0.0f);

    //Bottom Wall
    Position bWallPos(0.0f, 0.0f, 0.0f);
    BoundingBox2D bWallHBox(bWallPos, wallVol);

    _bottomWall = new GameObject("bottomWall", bWallPos, this);
    _bottomWall->setVolume(wallVol);
    _bottomWall->setHitBox(bWallHBox);
    _bottomWall->setAppearance(pongAppearance);
    _bottomWall->setCollidable(true);
    _bottomWall->setSolid(true);
    _bottomWall->setMobile(true);
    _bottomWall->setPlayable(false);
    _bottomWall->setInteractive(false);

    //Top Wall
    Position tWallPos(0.0f, _screenHeight-wallVol.height, 0.0f);
    BoundingBox2D tWallHBox(tWallPos, wallVol);

    _topWall = new GameObject("topWall", tWallPos, this);
    _topWall->setVolume(wallVol);
    _topWall->setHitBox(tWallHBox);
    _topWall->setAppearance(pongAppearance);
    _topWall->setCollidable(true);
    _topWall->setSolid(true);
    _topWall->setMobile(true);
    _topWall->setPlayable(false);
    _topWall->setInteractive(false);

}

void PongState::keyPressEvent(QKeyEvent *k) {
    switch(k->key()) {
        case Qt::Key_Up:
            _p1PaddleUp = true;
            break;
        case Qt::Key_Down:
            _p1PaddleDown = true;
            break;
        case Qt::Key_W:
            _p2PaddleUp = true;
            break;
        case Qt::Key_S:
            _p2PaddleDown = true;
            break;
        default :
            break;
    }
    k->accept();
}

void PongState::keyReleaseEvent(QKeyEvent *k) {
    switch(k->key()) {
        case Qt::Key_Up:
            _p1PaddleUp = false;
            break;
        case Qt::Key_Down:
            _p1PaddleDown = false;
            break;
        case Qt::Key_W:
            _p2PaddleUp = false;
            break;
        case Qt::Key_S:
            _p2PaddleDown = false;
            break;
        default :
            break;
    }
    k->accept();
}

