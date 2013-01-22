#include "pongstate.h"
#include <QMessageBox>

PongState::PongState(int screenWidth, int screenHeight,
                     QWidget* parent):
    GameState(screenWidth, screenHeight, parent),
    _p1PaddleUp(false),
    _p1PaddleDown(false),
    _p2PaddleUp(false),
    _p2PaddleDown(false)
{
    //Seed the random number generator
    srand(time(NULL));
    setName(QString("Pong"));
    this->setFocusPolicy(Qt::StrongFocus);

    _paddleVelPerSec = (float)(screenHeight*1.5);
    _ballVelPerSec = _paddleVelPerSec*.85;
    qDebug() << "PongState::PongState(): paddleVelPerSec = " << _paddleVelPerSec;
    _playerOneScore = 0;
    _playerTwoScore = 0;
    _scoreToWin = 10;
}

PongState::~PongState()
{

}

void PongState::buildAssets()
{
    //Build the assets for the game.
    float paddleWidth = (float)(_screenWidth) / 20.0f;
    float paddleHeight = (float)(_screenHeight) / 4.0f;
    Volume paddleVol(paddleWidth, paddleHeight, 0.0f, false);
    float paddleStartY = ((float)(_screenHeight) * 0.5f) - (paddleHeight*0.5f);

    Appearance pongAppearance;
    pongAppearance.r = 1.0f;
    pongAppearance.g = 0.0f;
    pongAppearance.b = 0.0f;
    pongAppearance.alpha = 1.0f;
    pongAppearance.textured = false;

    //Player one starting position:
    Position p1Pos(0.0f, paddleStartY, 0.0f);
    BoundingBox2D p1HBox(p1Pos, paddleVol);

    _playerOne = new GameObject(QString("playerOne"), p1Pos, this);
    _playerOne->setPosition(p1Pos);
    _playerOne->setVolume(paddleVol);
    _playerOne->setHitBox(p1HBox);
    _playerOne->setAppearance(pongAppearance);
    _playerOne->setCollidable(true);
    _playerOne->setSolid(true);
    _playerOne->setMobile(true);
    _playerOne->setPlayable(true);
    _playerOne->setInteractive(false);

    _playerOne->print();

    //Player two starting position:
    Position p2Pos(_screenWidth-paddleWidth, paddleStartY, 0.0f);
    BoundingBox2D p2HBox(p2Pos, paddleVol);

    _playerTwo = new GameObject(QString("playerTwo"), p2Pos, this);
    _playerTwo->setPosition(p2Pos);
    _playerTwo->setVolume(paddleVol);
    _playerTwo->setHitBox(p2HBox);
    _playerTwo->setAppearance(pongAppearance);
    _playerTwo->setCollidable(true);
    _playerTwo->setSolid(true);
    _playerTwo->setMobile(true);
    _playerTwo->setPlayable(true);
    _playerTwo->setInteractive(false);

    _playerTwo->print();

    //Ball
    Position ballPos((_screenWidth*0.5f),(_screenHeight*0.5f),0.0f);
    Volume ballVol(_screenWidth*0.05f, _screenHeight*0.05f, 0.0f);
    BoundingBox2D ballHBox(ballPos, ballVol);
    _ball = new GameObject(QString("ball"), ballPos, this);
    _ball->setPosition(ballPos);
    _ball->setVolume(ballVol);
    _ball->setHitBox(ballHBox);
    _ball->setAppearance(pongAppearance);
    _ball->setCollidable(true);
    _ball->setSolid(true);
    _ball->setMobile(true);
    _ball->setPlayable(false);
    _ball->setInteractive(false);

    _ball->print();

    //Walls
    Volume wallVol(_screenWidth, _screenHeight*0.1f, 0.0f);

    //Bottom Wall
    Position bWallPos(0.0f, 0.0f, 0.0f);
    BoundingBox2D bWallHBox(bWallPos, wallVol);

    _bottomWall = new GameObject(QString("bottomWall"), bWallPos, this);
    _bottomWall->setPosition(bWallPos);
    _bottomWall->setVolume(wallVol);
    _bottomWall->setHitBox(bWallHBox);
    _bottomWall->setAppearance(pongAppearance);
    _bottomWall->setCollidable(true);
    _bottomWall->setSolid(true);
    _bottomWall->setMobile(true);
    _bottomWall->setPlayable(false);
    _bottomWall->setInteractive(false);

    _bottomWall->print();

    //Top Wall
    Position tWallPos(0.0f, _screenHeight-wallVol.height, 0.0f);
    BoundingBox2D tWallHBox(tWallPos, wallVol);

    _topWall = new GameObject(QString("topWall"), tWallPos, this);
    _topWall->setPosition(tWallPos);
    _topWall->setVolume(wallVol);
    _topWall->setHitBox(tWallHBox);
    _topWall->setAppearance(pongAppearance);
    _topWall->setCollidable(true);
    _topWall->setSolid(true);
    _topWall->setMobile(true);
    _topWall->setPlayable(false);
    _topWall->setInteractive(false);

    _topWall->print();

    _screen->addGameObject(_ball);
    _screen->addGameObject(_playerOne);
    _screen->addGameObject(_playerTwo);
    _screen->addGameObject(_topWall);
    _screen->addGameObject(_bottomWall);

}

void PongState::update(float dt)
{
    //qDebug() << QString("PongState::update(): called with %1 seconds").arg(dt);
    //Move according to user input
    _ball->update(dt);
    _playerOne->update(dt);
    _playerTwo->update(dt);

    //Check collision, readjust
    checkBallWallCollision();
    checkPaddleWallCollision();
    checkBallPaddleCollision();

    //Check score
    checkGoalScored();
}

void PongState::handleInput()
{
    //qDebug() << "PongState::handleInput()";
    Velocity p1Vel = _playerOne->getVelocity();
    Velocity p2Vel = _playerTwo->getVelocity();
    if( _p1PaddleUp ){
        p1Vel.y = _paddleVelPerSec;
    }else if(_p1PaddleDown ){
        p1Vel.y = -_paddleVelPerSec;
    }else{
        p1Vel.y = 0.0f;
    }
    _playerOne->setVelocity(p1Vel);

    if( _p2PaddleUp ){
        p2Vel.y = _paddleVelPerSec;
    }else if( _p2PaddleDown ){
        p2Vel.y = -_paddleVelPerSec;
    }else{
        p2Vel.y = 0.0f;
    }
    _playerTwo->setVelocity(p2Vel);
}

void PongState::startGame()
{
    _playerOneScore = 0;
    _playerTwoScore = 0;
    serveBall();
}

void PongState::keyPressEvent(QKeyEvent *k) {
    switch(k->key()) {
        case Qt::Key_Up:
            _p2PaddleUp = true;
            //qDebug() << "PongState::keyPressEvent(): pressed up key!";
            break;
        case Qt::Key_Down:
            _p2PaddleDown = true;
            //qDebug() << "PongState::keyPressEvent(): pressed down key!";
            break;
        case Qt::Key_W:
            _p1PaddleUp = true;
            //qDebug() << "PongState::keyPressEvent(): pressed w key!";
            break;
        case Qt::Key_S:
            _p1PaddleDown = true;
            //qDebug() << "PongState::keyPressEvent(): pressed s key!";
            break;
        default :
            break;
    }
    k->accept();
}

void PongState::keyReleaseEvent(QKeyEvent *k) {
    switch(k->key()) {
        case Qt::Key_Up:
            _p2PaddleUp = false;
            break;
        case Qt::Key_Down:
            _p2PaddleDown = false;
            break;
        case Qt::Key_W:
            _p1PaddleUp = false;
            break;
        case Qt::Key_S:
            _p1PaddleDown = false;
            break;
        default :
            break;
    }
    k->accept();
}

void PongState::checkBallWallCollision()
{
    BoundingBox2D ball = _ball->getHitBox();
    BoundingBox2D tWall = _topWall->getHitBox();
    BoundingBox2D bWall = _bottomWall->getHitBox();

    Position ballPos = _ball->getPosition();
    Velocity ballVel = _ball->getVelocity();
    Volume ballVol = _ball->getVolume();

    if( ball.intersectsY(tWall) ){
        ballPos.y = tWall.startY - ballVol.height;
        _ball->setPosition(ballPos);
        ballVel.y *= -1.0f;
        _ball->setVelocity(ballVel);
    }
    if( ball.intersectsY(bWall) ){
        ballPos.y = bWall.endY;
        _ball->setPosition(ballPos);
        ballVel.y *= -1.0f;
        _ball->setVelocity(ballVel);
    }
}

void PongState::checkPaddleWallCollision()
{
    BoundingBox2D tWall = _topWall->getHitBox();
    BoundingBox2D bWall = _bottomWall->getHitBox();
    BoundingBox2D p1Paddle = _playerOne->getHitBox();
    BoundingBox2D p2Paddle = _playerTwo->getHitBox();

    if( p1Paddle.intersectsY(tWall) ){
        Velocity p1Vel = _playerOne->getVelocity();
        Position p1Pos = _playerOne->getPosition();
        Position tWallPos = _topWall->getPosition();
        Volume p1Vol = _playerOne->getVolume();
        p1Vel.y = 0.0f;
        p1Pos.y = (tWallPos.y - p1Vol.height);
        _playerOne->setVelocity(p1Vel);
        _playerOne->setPosition(p1Pos);
    }
    if( p2Paddle.intersectsY(tWall) ){
        Velocity p2Vel = _playerTwo->getVelocity();
        Position p2Pos = _playerTwo->getPosition();
        Position tWallPos = _topWall->getPosition();
        Volume p2Vol = _playerTwo->getVolume();
        p2Vel.y = 0.0f;
        p2Pos.y = (tWallPos.y - p2Vol.height);
        _playerTwo->setVelocity(p2Vel);
        _playerTwo->setPosition(p2Pos);
    }
    if( p1Paddle.intersectsY(bWall) ){
        Velocity p1Vel = _playerOne->getVelocity();
        Position p1Pos = _playerOne->getPosition();
        Position bWallPos = _bottomWall->getPosition();
        Volume bWallVol = _bottomWall->getVolume();
        p1Vel.y = 0.0f;
        p1Pos.y = ((bWallPos.y + bWallVol.height));
        _playerOne->setVelocity(p1Vel);
        _playerOne->setPosition(p1Pos);
    }
    if( p2Paddle.intersectsY(bWall) ){
        Velocity p2Vel = _playerTwo->getVelocity();
        Position p2Pos = _playerTwo->getPosition();
        Position bWallPos = _bottomWall->getPosition();
        Volume bWallVol = _bottomWall->getVolume();
        p2Vel.y = 0.0f;
        p2Pos.y = ((bWallPos.y + bWallVol.height));
        _playerTwo->setVelocity(p2Vel);
        _playerTwo->setPosition(p2Pos);
    }
}

void PongState::checkBallPaddleCollision()
{
    BoundingBox2D ball = _ball->getHitBox();
    BoundingBox2D p1Paddle = _playerOne->getHitBox();
    BoundingBox2D p2Paddle = _playerTwo->getHitBox();

    if( (ball.intersectsX(p1Paddle) && ball.intersectsY(p1Paddle)) ||
        (ball.intersectsX(p2Paddle) && ball.intersectsY(p2Paddle)) ){
        Velocity ballV = _ball->getVelocity();
        ballV.x *= -1.0f;
        _ball->setVelocity(ballV);
    }
}

void PongState::checkGoalScored()
{
    Position ballPos = _ball->getPosition();
    bool goalScored = false;
    if( ballPos.x < 0.0f ){
        _playerTwoScore++;
        goalScored = true;

    }else if( ballPos.x > _screenWidth ){
        _playerOneScore++;
        goalScored = true;
    }
    //check for win
    if( (_playerOneScore == _scoreToWin) ||
        (_playerTwoScore == _scoreToWin) ){
        int winner = (_playerOneScore == _scoreToWin ? 1 : 2);
        //Handle any score stuff
        QMessageBox::information(this, "Winner",
                                 QString("Player %1 wins!").arg(winner));
        emit gameOver();
    }else if(goalScored){
        serveBall();
    }
}

void PongState::serveBall()
{
    Position ballPos((_screenHeight*0.5f),(_screenHeight*0.5f),0.0f);
    _ball->setPosition(ballPos);

    //Set to a random velocity direction
    float randMult = ((float)rand() / (float)RAND_MAX);
    float coinFlipVert = ((float)rand() / (float)RAND_MAX);
    float coinFlipHoriz = ((float)rand() / (float)RAND_MAX);
    //Chooses a random x-component to the velocity but
    //guarantees that it is at least 100 pixels per second
    //in the horizontal.
    float xComp = (randMult*(_ballVelPerSec-100.0f))+100.0f;
    if( coinFlipHoriz > 0.5f ){
        xComp *= -1.0f;
    }
    float yComp = sqrt(pow(_ballVelPerSec, 2.0f) - pow(xComp, 2.0f));
    if( coinFlipVert > 0.5f ){
        yComp *= -1.0f;
    }
    Velocity ballVel(xComp, yComp, 0.0f);
    _ball->setVelocity(ballVel);

}
